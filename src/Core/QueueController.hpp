// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_QUEUE_CONTROLLER_HPP
#define CORE_QUEUE_CONTROLLER_HPP

#include "ActionResult.hpp"
#include "StatusResult.hpp"
#include "Request.hpp"
#include "Notification.hpp"

#include <functional>

namespace Core {

class IMessageQueue;

class QueueController {
  TYPE_PTRS(QueueController)
  public:
    QueueController(std::string controllerId, IMessageQueue& messageQueue);

    std::string getId() const { return controllerId; }

    StatusResult::Unique sendNotification(std::string receiver,
      ActionType actionType, std::string resource, IEntity::Shared result);

    StatusResult::Unique broadcastNotification(ActionType actionType,
      std::string resource, IEntity::Shared result);

    bool canProcessRequest(const Request& request);
    ActionResult::Unique processRequest(const Request& request);

    void setCanProcessRequest(std::function<bool(const Request&)> canProcessRequestHandler) {
      this->canProcessRequestHandler = canProcessRequestHandler;
    }
    void setProcessRequest(std::function<ActionResult::Unique(const Request&)> processRequest) {
      this->processRequestHandler = processRequest;
    }

  private:
    std::string controllerId;
    IMessageQueue& messageQueue;
    std::function<bool(const Request&)> canProcessRequestHandler;
    std::function<ActionResult::Unique(const Request&)> processRequestHandler;
};

}

#endif /* end of include guard: CORE_QUEUE_CONTROLLER_HPP */
