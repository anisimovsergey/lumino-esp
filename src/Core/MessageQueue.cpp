#include "MessageQueue.hpp"

#include "Memory.hpp"

using namespace Core;

std::unique_ptr<StatusResult>
MessageSender::send(std::shared_ptr<Message> message) {
  return StatusResult::OK();
}

void
MessageQueue::loop() {
  while (!actions.empty())
  {
    actions.front()();
    actions.pop();
  }
}

void
MessageQueue::post(TAction action) {
    actions.push(action);
}

std::unique_ptr<IMessageSender>
MessageQueue::addSender(
  String senderId,
  OnResponseHandler onResponseHandler,
  OnNotificationHandler onNotificationHandler) {
  return make_unique<MessageSender>();
}

void
MessageQueue::addBroadcastListener(
  OnBroadcastMessageHandler onBroadcastMessageHandler) {

}
