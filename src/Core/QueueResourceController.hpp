// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_QUEUE_RESOURCE_CONTROLLER_HPP
#define CORE_QUEUE_RESOURCE_CONTROLLER_HPP

#include "QueueController.hpp"

namespace Core {

class IMessageQueue;

template<typename T>
class QueueResourceController {
  TYPE_PTRS(QueueResourceController<T>)
  typedef typename T::Unique TUnique;
  public:
    QueueResourceController(QueueController::Shared queueController) :
      queueController(queueController), typeId(T::TypeId) {
    }

    void setOnGetRequestHandler(std::function<Core::IActionResult::Unique()> onGetRequestHandler) {
      this->onGetRequestHandler = onGetRequestHandler;
    }
    void setOnCreateRequestHandler(std::function<Core::StatusResult::Unique(const T&)> onCreateRequestHandler) {
      this->onCreateRequestHandler = onCreateRequestHandler;
    }
    void setOnUpdateRequestHandler(std::function<Core::StatusResult::Unique(const T&)> onUpdateRequestHandler) {
      this->onUpdateRequestHandler = onUpdateRequestHandler;
    }
    void setOnDeleteRequestHandler(std::function<Core::StatusResult::Unique()> onDeleteRequestHandler) {
      this->onDeleteRequestHandler = onDeleteRequestHandler;
    }

    void sendCreateNotification(TUnique object) {
      auto notification = Notification::makeShared(ActionType::Create, typeId, std::move(object));
      queueController->broadcastNotification(notification);
    }
    void sendUpdateNotification(TUnique object) {
      auto notification = Notification::makeShared(ActionType::Update, typeId, std::move(object));
      queueController->broadcastNotification(notification);
    }
    void sendDeleteNotification() {
      auto request = Notification::makeShared(ActionType::Delete, typeId, StatusResult::NoContent("Resource was deleted"));
      queueController->broadcastNotification(request);
    }
  private:
    QueueController::Shared queueController;
    String typeId;
    std::function<Core::IActionResult::Unique()> onGetRequestHandler;
    std::function<Core::StatusResult::Unique(const T&)> onCreateRequestHandler;
    std::function<Core::StatusResult::Unique(const T&)> onUpdateRequestHandler;
    std::function<Core::StatusResult::Unique()> onDeleteRequestHandler;
};

}

#endif /* end of include guard: CORE_QUEUE_RESOURCE_CONTROLLER_HPP */
