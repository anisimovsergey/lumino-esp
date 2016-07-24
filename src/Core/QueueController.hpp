// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_QUEUE_CONTROLLER_HPP
#define CORE_QUEUE_CONTROLLER_HPP

#include "ActionResult.hpp"
#include "IMessage.hpp"

#include <functional>

namespace Core {

class IMessageQueue;

class QueueController {
  TYPE_PTRS(QueueController)
  public:
    QueueController(String controllerId, IMessageQueue& messageQueue);

    StatusResult::Unique broadcastNotification(Notification::Shared notification);

    bool canProcessRequest(const Request& request);
    StatusResult::Unique processRequest(const Request& request);

    void setCanProcessRequest(std::function<bool(const Request&)> canProcessRequestHandler) {
      this->canProcessRequestHandler = canProcessRequestHandler;
    }

    void processRequest(std::function<StatusResult::Unique(const Request&)> processRequest) {
      this->processRequestHandler = processRequestHandler;
    }

  private:
    String controllerId;
    IMessageQueue& messageQueue;
    std::function<bool(const Request&)> canProcessRequestHandler;
    std::function<StatusResult::Unique(const Request&)> processRequestHandler;
};

}

#endif /* end of include guard: CORE_QUEUE_CONTROLLER_HPP */
