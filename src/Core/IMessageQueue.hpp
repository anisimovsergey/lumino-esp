// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_MESSAGE_QUEUE_HPP
#define CORE_I_MESSAGE_QUEUE_HPP

#include "ILoopedService.hpp"
#include "ActionResult.hpp"
#include "IMessage.hpp"

#include <WString.h>

#include <memory>
#include <functional>

namespace Core {

class IMessageSender  {
  public:
    virtual ~IMessageSender();

    virtual std::unique_ptr<StatusResult>
      send(std::shared_ptr<Message> message) = 0;
};

class IMessageQueue : public ILoopedService {
  public:
    virtual ~IMessageQueue();

    typedef std::function<void()> TAction;
    virtual void post(TAction action) = 0;

    typedef std::function<void()> OnResponseHandler;
    typedef std::function<void()> OnNotificationHandler;
    typedef std::function<void()> OnBroadcastMessageHandler;

    virtual std::unique_ptr<IMessageSender> addSender(
      String senderId,
      OnResponseHandler onResponseHandler,
      OnNotificationHandler onNotificationHandler) = 0;

    virtual void addBroadcastListener(
      OnBroadcastMessageHandler onBroadcastMessageHandler) = 0;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_QUEUE_HPP */
