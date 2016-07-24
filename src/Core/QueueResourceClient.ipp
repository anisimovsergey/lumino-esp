// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_QUEUE_RESOURCE_CLIENT_IPP
#define CORE_QUEUE_RESOURCE_CLIENT_IPP

#include "Core/Logger.hpp"

namespace Core {

template <typename T>
QueueResourceClient<T>::QueueResourceClient(QueueClient::Shared queueClient) :
  queueClient(queueClient), typeId(T::TypeId) {

  queueClient->setOnResponse(
    std::bind(&QueueResourceClient<T>::onResponse, this, std::placeholders::_1));
  queueClient->setOnNotification(
    std::bind(&QueueResourceClient<T>::onNotification, this, std::placeholders::_1));
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::getResource() {
  auto request = Request::makeShared(ActionType::Get, typeId);
  return queueClient->sendMessage(request);
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::createResource(TUnique resource) {
  auto request = Request::makeShared(ActionType::Create, typeId, resource);
  return queueClient->sendMessage(request);
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::updateResource(TUnique resource) {
  auto request = Request::makeShared(ActionType::Update, typeId, resource);
  return queueClient->sendMessage(request);
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::deleteResource() {
  auto request = Request::makeShared(ActionType::Delete, typeId);
  return queueClient->sendMessage(request);
}

template <typename T>
void
QueueResourceClient<T>::onResponse(const Response& response) {
  if (response.getActionType() == ActionType::Get) {
    if (onGetResponseHandler)
      onGetResponseHandler(response);
  } else if (response.getActionType() == ActionType::Create) {
    if (onCreateResponseHandler)
      onCreateResponseHandler(response);
  } else if (response.getActionType() == ActionType::Update) {
    if (onUpdateResponseHandler)
      onUpdateResponseHandler(response);
  } else if (response.getActionType() == ActionType::Delete) {
    if (onDeleteResponseHandler)
      onDeleteResponseHandler(response);
  }
}

template <typename T>
void
QueueResourceClient<T>::onNotification(const Notification& notification) {
  if (notification.getActionType() == ActionType::Create) {
    if (onCreateNotificationHandler) {
      auto object = T::cast(notification.getContent());
      if (object)
        onCreateNotificationHandler(*object);
      else
        Logger::error("Expeceted content of '" + String(T::TypeId) + "' type.");
    }
  } else if (notification.getActionType() == ActionType::Update) {
    if (onUpdateNotificationHandler) {
      auto object = T::cast(notification.getContent());
      if (object)
        onUpdateNotificationHandler(*object);
      else
        Logger::error("Expeceted content of '" + String(T::TypeId) + "' type.");
    }
  } else if (notification.getActionType() == ActionType::Delete) {
    if (onDeleteNotificationHandler)
      onDeleteNotificationHandler();
  }
}

}

#endif /* end of include guard: CORE_QUEUE_RESOURCE_CLIENT_IPP */
