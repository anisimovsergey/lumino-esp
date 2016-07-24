// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_QUEUE_RESOURCE_CLIENT_HPP
#define CORE_QUEUE_RESOURCE_CLIENT_HPP

#include "QueueClient.hpp"

namespace Core {

template <typename T>
class QueueResourceClient {
  TYPE_PTRS(QueueResourceClient)
  typedef typename T::Unique TUnique;
  public:
    QueueResourceClient(QueueClient::Shared queueClient) :
      queueClient(queueClient), typeId(T::TypeId)     {
    }

    StatusResult::Unique getResource() {
      auto request = Request::makeShared(ActionType::Get, typeId);
      return queueClient->sendMessage(request);
    }

    StatusResult::Unique createResource(TUnique resource) {
      auto request = Request::makeShared(ActionType::Create, typeId, resource);
      return queueClient->sendMessage(request);
    }

    StatusResult::Unique updateResource(TUnique resource) {
      auto request = Request::makeShared(ActionType::Update, typeId, resource);
      return queueClient->sendMessage(request);
    }

    StatusResult::Unique deleteResource() {
      auto request = Request::makeShared(ActionType::Delete, typeId);
      return queueClient->sendMessage(request);
    }

    void setOnGetResponse(std::function<void(const Response&)> onGetResponse) {
      onGetResponseHandler = onGetResponse;
    }
    void setOnCreateResponse(std::function<void(const Response&)> onCreateResponse) {
      onCreateResponseHandler = onCreateResponse;
    }
    void setOnUpdateResponse(std::function<void(const Response&)> onUpdateResponse) {
      onUpdateResponseHandler = onUpdateResponse;
    }
    void setOnDeleteResponse(std::function<void(const Response&)> onDeleteResponse) {
      onDeleteResponseHandler = onDeleteResponse;
    }

    void setOnGetNotification(std::function<void(const T&)> onGetNotification) {
      onGetNotificationHandler = onGetNotification;
    }
    void setOnCreateNotification(std::function<void(const T&)> onCreateNotification) {
      onCreateNotificationHandler = onCreateNotification;
    }
    void setOnUpdateNotification(std::function<void(const T&)> onUpdateNotification) {
      onUpdateNotificationHandler = onUpdateNotification;
    }
    void setOnDeleteNotification(std::function<void()> onDeleteNotification) {
      onDeleteNotificationHandler = onDeleteNotification;
    }

  private:
    QueueClient::Shared queueClient;
    String typeId;
    std::function<void(const Response&)> onGetResponseHandler;
    std::function<void(const Response&)> onCreateResponseHandler;
    std::function<void(const Response&)> onUpdateResponseHandler;
    std::function<void(const Response&)> onDeleteResponseHandler;
    std::function<void(const T&)> onGetNotificationHandler;
    std::function<void(const T&)> onCreateNotificationHandler;
    std::function<void(const T&)> onUpdateNotificationHandler;
    std::function<void()> onDeleteNotificationHandler;
};

}

#endif /* end of include guard: CORE_QUEUE_RESOURCE_CLIENT_HPP */
