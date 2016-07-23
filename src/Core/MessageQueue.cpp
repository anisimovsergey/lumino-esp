#include "MessageQueue.hpp"

#include "Memory.hpp"
#include "Logger.hpp"

using namespace Core;

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
        result = controller->onRequest(*request);
      } else {
        result = StatusResult::NotFound("Unable to find a receiver.");
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
        Logger::error("Unable to find receiver '" + receiver + "'");
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

void
MessageQueue::addClient(QueueClient::Shared client) {
  clients.push_back(client);
}

void
MessageQueue::addController(QueueController::Shared controller) {
  controllers.push_back(controller);
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
    if (controller->getResource() == request.getResource())
      return controller;
  }
  return nullptr;
}
