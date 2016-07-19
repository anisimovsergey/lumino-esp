// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_MESSAGE_QUEUE_HPP
#define CORE_MESSAGE_QUEUE_HPP

#include "IMessageQueue.hpp"

#include <queue>
#include <list>
#include <vector>

namespace Core {

class MessageComparer;

class MessageQueue : public IMessageQueue {
  public:
    // From ILoopedService
    virtual void loop() override;

    // From IMessageQueue
    virtual std::unique_ptr<StatusResult> send(
      String senderId, std::shared_ptr<Message> message) override;
    virtual std::unique_ptr<StatusResult> notify(
      String receiverId, std::shared_ptr<Notification> notification) override;
    virtual std::unique_ptr<StatusResult> broadcast(
      std::shared_ptr<Notification> notification) override;
    virtual void addMessageSender(
      std::shared_ptr<IMessageSender> sender) override;
    virtual void addMessageReceiver(
      std::shared_ptr<IMessageReceiver> receiver) override;
    virtual void addMessageListener(
      std::shared_ptr<IMessageListener> listener) override;

  private:
    class MessageComparer
    {
      bool reverse;
    public:
      bool operator() (const std::shared_ptr<Message>& lhs, const std::shared_ptr<Message>&rhs) const
      {
        return (lhs->getPriority() > rhs->getPriority());
      }
    };

    std::priority_queue<std::shared_ptr<Message>, std::vector<std::shared_ptr<Message>, MessageComparer> messages;
    std::list<std::shared_ptr<IMessageSender>> senders;
    std::list<std::shared_ptr<IMessageReceiver>> receivers;
    std::list<std::shared_ptr<IMessageListener>> listeners;

    std::shared_ptr<IMessageSender> getMessageSender(String senderId);
    std::shared_ptr<IMessageReceiver> getMessageReceiver(const Request& request);
};

}

#endif /* end of include guard: CORE_MESSAGE_QUEUE_HPP */
