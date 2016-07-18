#include "MessageQueue.hpp"

#include "Memory.hpp"
#include "Logger.hpp"

using namespace Core;

void
MessageQueue::loop() {
  while (!actions.empty())
  {
    actions.front()();
    actions.pop();
  }
  while (!messages.empty())
  {
    Logger::message("Message queue is not empty");
    auto message = messages.front();

    auto request = dynamic_cast_to_shared<Request>(message);
    if (request) {
      Logger::message("Processing request");
      // Insert code here for finding a processor
      // IF the message is a Request and unable to find a processor for this message
      // THEN send response to the sender
      auto result = StatusResult::NotFound("Unable to find a processor for this type of request.");
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
      // The sender is the message queue, move it to const
      response->addTag("sender", "messageQueue");
      messages.push(response);
    } else {
      Logger::message("It's not a request");
    }
    auto response = dynamic_cast_to_shared<Response>(message);
    if (response) {
      Logger::message("Processing response");
      // Try to find a receiver for this message.
      auto receiver = getMessageReceiver(response->getTag("receiver"));
      if (receiver) {
        receiver->onResponse(response);
      }
      // If can't find, just log, we can't do much the sender is gone.
    } else {
      Logger::message("It's not a response");
    }
    Logger::message("Removing message from the queue");
    messages.pop();
    Logger::message("Removed.");
  }
}

void
MessageQueue::post(std::function<void()> action) {
    actions.push(action);
}

std::unique_ptr<StatusResult>
MessageQueue::send(
  String senderId, std::shared_ptr<Message> message) {
  message->addTag("sender", senderId);
  messages.push(message);
  return StatusResult::OK();
}

void
MessageQueue::addMessageReceiver(
  String receiverId, IMessageReceiver* receiver) {

  receivers.push_back(std::make_tuple(receiverId, receiver));
}

IMessageReceiver*
MessageQueue::getMessageReceiver(String receiverId) {
  for(auto tuple: receivers) {
    if (std::get<0>(tuple) == receiverId)
      return std::get<1>(tuple);
  }
  return nullptr;
}
