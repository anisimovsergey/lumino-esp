#include "MessageQueue.hpp"

#include "Memory.hpp"
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
    Logger::error("Unknown message type '" + String(message->getTypeId()) + "'.");
  }
}

StatusResult::Unique
MessageQueue::sendMessage(Message::Shared message) {
  messages.push(message);
  return StatusResult::OK();
}

QueueClient::Shared
MessageQueue::createClient(String clientId) {
  auto client = QueueClient::makeShared(clientId, *this);
  clients.push_back(client);
  return client;
}

QueueController::Shared
MessageQueue::createController(String controllerId) {
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
  IActionResult::Unique result;
  auto controller = getControllerFor(request);
  if (controller) {
    result = controller->processRequest(request);
  } else {
    Logger::error("Unable to find a controller.");
    result = StatusResult::NotFound("Unable to find a controller.");
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
  for(auto client: clients) {
    client->onNotification(notification);
  }
}

QueueClient::Shared
MessageQueue::getClient(String clientId) {
  for(auto client: clients) {
    if (client->getId() == clientId)
      return client;
  }
  return nullptr;
}

QueueController::Shared
MessageQueue::getControllerFor(const Request& request) {
  for(auto controller: controllers) {
    if (controller->canProcessRequest(request))
      return controller;
  }
  return nullptr;
}

Response::Shared
MessageQueue::createResponseFor(const Request& request,
  IActionResult::Unique result, const QueueController* controller) {
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
