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
      auto receiver = getMessageReceiver(*request);
      if (receiver) {
        result = receiver->onRequest(request);
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
      auto sender = getMessageSender(receiver);
      if (sender) {
        sender->onResponse(response);
      } else {
        Logger::error("Unable to find receiver '" + receiver + "'");
      }
    }
    auto notification = castToShared<Notification>(message);
    if (notification) {
      auto receiver = notification->getTag("receiver");
      if (receiver != "") {
        Logger::message("Processing a notification for '" + receiver + "'");
        auto sender = getMessageSender(receiver);
        if (sender) {
          sender->onNotification(notification);
        }
      } else {
        Logger::message("Processing a broadcast notification");
        for(auto listener: listeners) {
          listener->onBroadcast(notification);
        }
      }
    }
    messages.pop();
  }
}

StatusResult::Unique
MessageQueue::send(
  String senderId, Request::Shared request) {
  request->addTag("sender", senderId);
  messages.push(request);
  return StatusResult::OK();
}

StatusResult::Unique
MessageQueue::notify(
  const Request& request, Notification::Shared notification) {
  notification->addTag("fromClient", request.getTag("fromClient"));
  notification->addTag("receiver", request.getTag("sender"));
  messages.push(notification);
  return StatusResult::OK();
}

StatusResult::Unique
MessageQueue::broadcast(
  String sender,
  Notification::Shared notification) {
  notification->addTag("sender", sender);
  messages.push(notification);
  return StatusResult::OK();
}

void
MessageQueue::addMessageSender(IMessageSender::Shared sender) {
  senders.push_back(sender);
}

void
MessageQueue::addMessageReceiver(IMessageReceiver::Shared receiver) {
  receivers.push_back(receiver);
}

void
MessageQueue::addMessageListener(IMessageListener::Shared listener) {
  listeners.push_back(listener);
}

IMessageSender::Shared
MessageQueue::getMessageSender(String senderId) {
  for(auto sender: senders) {
    if (sender->getSenderId() == senderId)
      return sender;
  }
  return nullptr;
}

IMessageReceiver::Shared
MessageQueue::getMessageReceiver(const Request& request) {
  for(auto receiver: receivers) {
    if (receiver->getActionType() == request.getActionType() &&
        receiver->getResource() == request.getResource())
      return receiver;
  }
  return nullptr;
}
