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

class IMessageReceiver {
public:
  virtual ~IMessageReceiver();

  virtual void onResponse(std::shared_ptr<Response> response) = 0;
  virtual void onNotification() = 0;
  virtual void onBroadcast() = 0;
};

class IMessageQueue : public ILoopedService {
  public:
    virtual ~IMessageQueue();

    virtual void post(std::function<void()> action) = 0;

    virtual std::unique_ptr<StatusResult> send(
      String senderId, std::shared_ptr<Message> message) = 0;

    virtual void addMessageReceiver(
      String receiverId, IMessageReceiver* receiver) = 0;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_QUEUE_HPP */
