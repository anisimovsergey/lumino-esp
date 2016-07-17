// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_MESSAGE_QUEUE_HPP
#define CORE_MESSAGE_QUEUE_HPP

#include "IMessageQueue.hpp"

#include <queue>

namespace Core {

class MessageSender : public IMessageSender {

  virtual std::unique_ptr<StatusResult>
    send(std::shared_ptr<Message> message) override;

};

class MessageQueue : public IMessageQueue {
  public:
    // From ILoopedService
    virtual void loop() override;

    // From IMessageQueue
    virtual void post(TAction action) override;
    //virtual void postMessage() override;
    //virtual std::unique_ptr<EventHandler>subscribe();
    //virtual void unsubcribe(std::unique_ptr<EventHandler>)

    virtual std::unique_ptr<IMessageSender> addSender(
      String senderId,
      OnResponseHandler onResponseHandler,
      OnNotificationHandler onNotificationHandler) override;

    virtual void addBroadcastListener(
      OnBroadcastMessageHandler onBroadcastMessageHandler) override;

  private:
    std::queue<TAction> actions;
};

}

#endif /* end of include guard: CORE_MESSAGE_QUEUE_HPP */
