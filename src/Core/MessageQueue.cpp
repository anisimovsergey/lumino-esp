#include "MessageQueue.hpp"

#include "Memory.hpp"
#include "Logger.hpp"

using namespace Core;

void
MessageQueue::loop() {
  while (!messages.empty())
  {
    Logger::message("Message queue is not empty");
    auto message = messages.front();

    auto request = dynamic_cast_to_shared<Request>(message);
    if (request) {
      Logger::message("Processing request");
      std::unique_ptr<StatusResult> result;
      auto receiver = getMessageReceiver(*request);
      if (receiver) {
        result = receiver->onRequest(request);
      } else {
        result = StatusResult::NotFound("Unable to find a processor for this type of request.");
      }
      auto response = std::make_shared<Response>(
        request->getActionType(),
        request->getResource(),
        std::move(result)
      );
      // Copy all tags
      // TODO: Move it to the constructor, the next line should be generic!
      response->addTag("fromClient", request->getTag("fromClient"));
      // Send back to the sender
      response->addTag("receiver", request->getTag("sender"));
      // TODO: Set a proper sender or "messageQueue"
      // response->addTag("sender", "messageQueue");
      messages.push(response);
    }
    auto response = dynamic_cast_to_shared<Response>(message);
    if (response) {
      Logger::message("Processing response");
      // Try to find a receiver for this message.
      auto sender = getMessageSender(response->getTag("receiver"));
      if (sender) {
        sender->onResponse(response);
      }
      // If can't find, just log, we can't do much the sender is gone.
    }
    auto notification = dynamic_cast_to_shared<Notification>(message);
    if (notification) {
      Logger::message("Processing notification");
      auto receiverId = notification->getTag("receiver");
      if (receiverId != "") {
        Logger::message("Receiver id " + receiverId);
        auto sender = getMessageSender(receiverId);
        if (sender) {
          sender->onNotification(notification);
        }
      } else {
        for(auto listener: listeners) {
          listener->onBroadcast(notification);
        }
      }
    }
    messages.pop();
  }
}

std::unique_ptr<StatusResult>
MessageQueue::send(
  String senderId, std::shared_ptr<Message> message) {
  Logger::message("Message sent from " + senderId);
  message->addTag("sender", senderId);
  messages.push(message);
  return StatusResult::OK();
}

std::unique_ptr<StatusResult>
MessageQueue::notify(
  String receiverId, std::shared_ptr<Notification> notification) {
  Logger::message("Notification sent back to " + receiverId);
  notification->addTag("receiver", receiverId);
  messages.push(notification);
  return StatusResult::OK();
}

std::unique_ptr<StatusResult>
MessageQueue::broadcast(
  std::shared_ptr<Notification> notification) {
  Logger::message("Notification broadcasted.");
  messages.push(notification);
  return StatusResult::OK();
}

void
MessageQueue::addMessageSender(std::shared_ptr<IMessageSender> sender) {
  senders.push_back(sender);
}

void
MessageQueue::addMessageReceiver(std::shared_ptr<IMessageReceiver> receiver) {
  receivers.push_back(receiver);
}

void
MessageQueue::addMessageListener(std::shared_ptr<IMessageListener> listener) {
  listeners.push_back(listener);
}

std::shared_ptr<IMessageSender>
MessageQueue::getMessageSender(String senderId) {
  for(auto sender: senders) {
    if (sender->getSenderId() == senderId)
      return sender;
  }
  return nullptr;
}

std::shared_ptr<IMessageReceiver>
MessageQueue::getMessageReceiver(const Request& request) {
  for(auto receiver: receivers) {
    if (receiver->getActionType() == request.getActionType() &&
        receiver->getResource() == request.getResource())
      return receiver;
  }
  return nullptr;
}
