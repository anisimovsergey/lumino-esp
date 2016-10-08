#include "MessageQueue.hpp"

#include "Casting.hpp"
#include "Logger.hpp"

using namespace Core;

MessageQueue::MessageQueue() {
}

MessageQueue::~MessageQueue() {
}

void
MessageQueue::loop() {
  while (!messages.empty())
  {
    auto message = messages.top();
    messages.pop();
    auto request = castToShared<Request>(message);
    if (request) {
      processRequest(*request);
      continue;
    }
    auto response = castToShared<Response>(message);
    if (response) {
      processResponse(*response);
      continue;
    }
    auto notification = castToShared<Notification>(message);
    if (notification) {
      processNotification(*notification);
      continue;
    }
    Logger::error("Unknown message type '" + std::string(message->getTypeId()) + "'.");
  }
}

StatusResult::Unique
MessageQueue::sendMessage(Message::Shared message) {
  messages.push(message);
  return StatusResult::OK();
}

QueueClient::Shared
MessageQueue::createClient(std::string clientId) {
  auto client = QueueClient::makeShared(clientId, *this);
  clients.push_back(client);
  return client;
}

QueueController::Shared
MessageQueue::createController(std::string controllerId) {
  auto controller = QueueController::makeShared(controllerId, *this);
  controllers.push_back(controller);
  return controller;
}

void
MessageQueue::removeClient(QueueClient::Shared client) {
  clients.remove(client);
}

void
MessageQueue::removeController(QueueController::Shared controller) {
  controllers.remove(controller);
}

void
MessageQueue::processRequest(const Request& request) {
  Logger::message("Processing a request from '" + request.getTag("sender") + "'");
  ActionResult::Unique result;
  auto controller = getControllerFor(request);
  if (controller) {
    result = controller->processRequest(request);
  } else {
    Logger::error("Unable to find a controller.");
    result = StatusResult::makeUnique(StatusCode::NotFound, "Unable to find a controller.");
  }
  auto response = createResponseFor(request, std::move(result), controller.get());
  messages.push(response);
}

void
MessageQueue::processResponse(const Response& response) {
  auto sender = response.getTag("sender");
  auto receiver = response.getTag("receiver");
  Logger::message("Processing a response from '" + sender + "' to '" + receiver + "'");
  auto client = getClient(receiver);
  if (client) {
    client->onResponse(response);
  } else {
    Logger::error("Unable to find client '" + receiver + "'");
  }
}

void
MessageQueue::processNotification(const Notification& notification) {
  auto sender = notification.getTag("sender");
  Logger::message("Broadcating a notification from '" + sender + "'.");
  std::list<QueueClient::Shared> deletedClients;
  auto receiver = notification.getTag("receiver");
  if (receiver != "") {
    auto client = getClient(receiver);
    if (client) {
      if (!client.unique()) {
  	    client->onNotification(notification);
      } else {
        deletedClients.push_back(client);
      }
    }
  } else {
    for(auto client: clients) {
      if (!client.unique()) {
  	    client->onNotification(notification);
      } else {
        deletedClients.push_back(client);
      }
    }
  }
  for(auto client: deletedClients) {
    clients.remove(client);
  }
}

QueueClient::Shared
MessageQueue::getClient(std::string clientId) {
  QueueClient::Shared queueClient;
  for(auto client: clients) {
    if (client->getId() == clientId) {
      queueClient = client;
      break;
    }
  }
  if (queueClient && queueClient.unique()) {
    clients.remove(queueClient);
    return nullptr;
  }
  return queueClient;
}

QueueController::Shared
MessageQueue::getControllerFor(const Request& request) {
  QueueController::Shared queueController;
  for(auto controller: controllers) {
    if (controller->canProcessRequest(request)) {
      queueController = controller;
      break;
    }
  }
  if (queueController && queueController.unique()) {
    controllers.remove(queueController);
    return nullptr;
  }
  return queueController;
}

Response::Shared
MessageQueue::createResponseFor(const Request& request,
  ActionResult::Unique result, const QueueController* controller) {
  auto response = Response::makeShared(request.getActionType(),
                                       request.getResource(),
                                       std::move(result));
  response->addTag("receiver", request.getTag("sender"));
  if (controller)
    response->addTag("sender", controller->getId());
  else
    response->addTag("sender", "messageQueue");
  return response;
}
