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

class MessageQueue : public IMessageQueue {
  public:
    // From ILoopedService
    virtual void loop() override;

    // From IMessageQueue
    virtual StatusResult::Unique send(
      String senderId, Message::Shared message) override;
    virtual StatusResult::Unique notify(
      const Request& request, Notification::Shared notification) override;
    virtual StatusResult::Unique broadcast(
      String sender,
      Notification::Shared notification) override;
    virtual void addMessageSender(
      IMessageSender::Shared sender) override;
    virtual void addMessageReceiver(
      IMessageReceiver::Shared receiver) override;
    virtual void addMessageListener(
      IMessageListener::Shared listener) override;

  private:
    class MessageComparer {
        bool reverse;
      public:
        bool operator() (const Message::Shared& lhs, const Message::Shared&rhs) const
        {
          return (lhs->getPriority() > rhs->getPriority());
        }
    };

    std::priority_queue<Message::Shared, std::vector<Message::Shared>, MessageComparer> messages;
    std::list<IMessageSender::Shared> senders;
    std::list<IMessageReceiver::Shared> receivers;
    std::list<IMessageListener::Shared> listeners;

    IMessageSender::Shared getMessageSender(String senderId);
    IMessageReceiver::Shared getMessageReceiver(const Request& request);
};

}

#endif /* end of include guard: CORE_MESSAGE_QUEUE_HPP */
