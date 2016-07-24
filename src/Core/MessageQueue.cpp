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
    auto request = castToShared<Request>(message);
    if (request) {
      Logger::message("Processing a request from '" + request->getTag("sender") + "'");
      StatusResult::Unique result;
      auto controller = getController(*request);
      if (controller) {
        result = controller->processRequest(*request);
      } else {
        result = StatusResult::NotFound("Unable to find a controller.");
      }
      auto response = Response::createFor(*request, std::move(result));
      messages.push(response);
    }
    auto response = castToShared<Response>(message);
    if (response) {
      auto receiver = response->getTag("receiver");
      Logger::message("Processing a response for '" + receiver + "'");
      auto client = getClient(receiver);
      if (client) {
        client->onResponse(*response);
      } else {
        Logger::error("Unable to find client '" + receiver + "'");
      }
    }
    auto notification = castToShared<Notification>(message);
    if (notification) {
      auto receiver = notification->getTag("receiver");
      if (receiver != "") {
        Logger::message("Processing a notification for '" + receiver + "'");
        auto client = getClient(receiver);
        if (client) {
          client->onNotification(*notification);
        }
      } else {
        Logger::message("Processing a broadcast notification");
        for(auto client: clients) {
          client->onNotification(*notification);
        }
      }
    }
    messages.pop();
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

QueueClient::Shared
MessageQueue::getClient(String clientId) {
  for(auto client: clients) {
    if (client->getId() == clientId)
      return client;
  }
  return nullptr;
}

QueueController::Shared
MessageQueue::getController(const Request& request) {
  for(auto controller: controllers) {
    if (controller->canProcessRequest(request))
      return controller;
  }
  return nullptr;
}
