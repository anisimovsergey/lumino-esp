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
#include <tuple>

namespace Core {

class MessageQueue : public IMessageQueue {
  public:
    // From ILoopedService
    virtual void loop() override;

    // From IMessageQueue
    virtual void post(std::function<void()> action) override;

    virtual std::unique_ptr<StatusResult> send(
      String senderId, std::shared_ptr<Message> message) override;

   virtual void addMessageSender(std::shared_ptr<IMessageSender> sender) override;
   virtual void addMessageReceiver(std::shared_ptr<IMessageReceiver> receiver) override;

  private:
    std::queue<std::function<void()>> actions; // TODO : this should be removed ASAP
    std::queue<std::shared_ptr<Message>> messages;
    std::list<std::shared_ptr<IMessageSender>> senders;
    std::list<std::shared_ptr<IMessageReceiver>> receivers;

    std::shared_ptr<IMessageSender> getMessageSender(String senderId);
    std::shared_ptr<IMessageReceiver> getMessageReceiver(const Request& request);
};

}

#endif /* end of include guard: CORE_MESSAGE_QUEUE_HPP */
