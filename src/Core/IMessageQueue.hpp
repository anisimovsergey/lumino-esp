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

class IMessageSender {
TYPE_PTRS(IMessageSender)
public:
  virtual ~IMessageSender();

  virtual String getSenderId() = 0;

  virtual void onResponse(Response::Shared response) = 0;
  virtual void onNotification(Notification::Shared notification) = 0;
};

class MessageSender : public IMessageSender {
public:
  MessageSender(String senderId,
    std::function<void(Response::Shared)> responseHandler,
    std::function<void(Notification::Shared)> notificationHandler) :
    senderId(senderId), responseHandler(responseHandler), notificationHandler(notificationHandler) {
  }

  virtual String getSenderId() override { return senderId; };

  virtual void onResponse(Response::Shared response) override {
    responseHandler(response);
  }

  virtual void onNotification(Notification::Shared notification) override {
    notificationHandler(notification);
  }

private:
  String senderId;
  std::function<void(Response::Shared)> responseHandler;
  std::function<void(Notification::Shared)> notificationHandler;
};

class IMessageListener {
TYPE_PTRS(IMessageListener)
public:
  ~IMessageListener();

  virtual void onBroadcast(Notification::Shared notification) = 0;
};

class MessageListener : public IMessageListener {
public:
  MessageListener(std::function<void(Notification::Shared)> broadcastHandler) : broadcastHandler(broadcastHandler) {
  }

  virtual void onBroadcast(Notification::Shared notification) override {
    broadcastHandler(notification);
  }
private:
  std::function<void(Notification::Shared)> broadcastHandler;
};

class IMessageReceiver {
TYPE_PTRS(IMessageReceiver)
public:
  virtual ~IMessageReceiver();

  virtual ActionType getActionType() = 0;
  virtual String getResource() = 0;

  virtual StatusResult::Unique onRequest(Request::Shared request) = 0;
};

class MessageReceiver : public IMessageReceiver {
protected:
  MessageReceiver(ActionType actionType, String resource) :
    actionType(actionType), resource(resource) {
  }

  virtual ActionType getActionType() override { return actionType; }
  virtual String getResource() override { return resource; }

private:
  ActionType actionType;
  String resource;
};

class GetMessageReceiver : public MessageReceiver {
public:
  GetMessageReceiver(String resource, std::function<StatusResult::Unique(Request::Shared)> handler) :
    MessageReceiver(ActionType::Get, resource), handler(handler) {
  }

  virtual StatusResult::Unique onRequest(Request::Shared request) override {
    return handler(request);
  }

private:
  std::function<StatusResult::Unique(Request::Shared)> handler;
};

class DeleteMessageReceiver : public MessageReceiver {
public:
  DeleteMessageReceiver(String resource, std::function<StatusResult::Unique(Request::Shared)> handler) :
    MessageReceiver(ActionType::Delete, resource), handler(handler) {
  }

  virtual StatusResult::Unique onRequest(Request::Shared request) override {
    return handler(request);
  }

private:
  std::function<StatusResult::Unique(Request::Shared)> handler;
};

template<class T>
class CreateMessageReceiver : public MessageReceiver {
public:
  CreateMessageReceiver(String resource, std::function<StatusResult::Unique(Request::Shared, const T&)> handler) :
    MessageReceiver(ActionType::Create, resource), handler(handler) {
  }

  virtual StatusResult::Unique onRequest(Request::Shared request) override {
    auto content = T::cast(request->getContent());
    if (content)
      return handler(request, *content);
    return StatusResult::InternalServerError("Expeceted content of '" + String(T::TypeId) + "' type.");
  }

private:
  std::function<StatusResult::Unique(Request::Shared, const T&)> handler;
};

template<class T>
class UpdateMessageReceiver : public MessageReceiver {
public:
  UpdateMessageReceiver(String resource, std::function<StatusResult::Unique(Request::Shared, const T&)> handler) :
    MessageReceiver(ActionType::Update, resource), handler(handler) {
  }

  virtual StatusResult::Unique onRequest(Request::Shared request) override {
    auto content = T::cast(request->getContent());
    if (content)
      return handler(request, *content);
    return StatusResult::InternalServerError("Expeceted content of '" + String(T::TypeId) + "' type.");
  }

private:
  std::function<StatusResult::Unique(Request::Shared, const T&)> handler;
};

class IMessageQueue : public ILoopedService {
  public:
    virtual ~IMessageQueue();

    virtual StatusResult::Unique send(
      String senderId, Message::Shared message) = 0;

    virtual StatusResult::Unique notify(
      const Request& request, Notification::Shared notification) = 0;

    virtual StatusResult::Unique broadcast(
      String sender,
      Notification::Shared notification) = 0;

    virtual void addMessageSender(
      IMessageSender::Shared sender) = 0;

    virtual void addMessageReceiver(
      IMessageReceiver::Shared receiver) = 0;

    virtual void addMessageListener(
      IMessageListener::Shared listener) = 0;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_QUEUE_HPP */
