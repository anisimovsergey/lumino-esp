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
public:
  virtual ~IMessageSender();

  virtual void onResponse(std::shared_ptr<Response> response) = 0;
  virtual void onNotification(std::shared_ptr<Notification> notification) = 0;
};

class IMessageListener {
public:
  ~IMessageListener();

  virtual void onBroadcast(std::shared_ptr<Notification> notification) = 0;
};

class IMessageReceiver {
public:
  virtual ~IMessageReceiver();

  virtual ActionType getActionType() = 0;
  virtual String getResource() = 0;

  virtual void onRequest(std::shared_ptr<Request> request) = 0;
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
  GetMessageReceiver(String resource, std::function<void(std::shared_ptr<Request>)> handler) :
    MessageReceiver(ActionType::Get, resource), handler(handler) {
  }

  virtual void onRequest(std::shared_ptr<Request> request) override {
    handler(request);
  }

private:
  std::function<void(std::shared_ptr<Request>)> handler;
};

class DeleteMessageReceiver : public MessageReceiver {
public:
  DeleteMessageReceiver(String resource, std::function<void(std::shared_ptr<Request>)> handler) :
    MessageReceiver(ActionType::Delete, resource), handler(handler) {
  }

  virtual void onRequest(std::shared_ptr<Request> request) override {
    handler(request);
  }

private:
  std::function<void(std::shared_ptr<Request>)> handler;
};

template<class T>
class CreateMessageReceiver : public MessageReceiver {
public:
  CreateMessageReceiver(String resource, std::function<void(std::shared_ptr<Request>, T*)> handler) :
    MessageReceiver(ActionType::Create, resource), handler(handler) {
  }

  virtual void onRequest(std::shared_ptr<Request> request) override {
    auto content = T::cast(request->getContent());
    if (content)
      handler(request);
  }

private:
  std::function<void(std::shared_ptr<Request>, T*)> handler;
};

template<class T>
class UpdateMessageReceiver : public MessageReceiver {
public:
  UpdateMessageReceiver(String resource, std::function<void(std::shared_ptr<Request>, T*)> handler) :
    MessageReceiver(ActionType::Update, resource), handler(handler) {
  }

  virtual void onRequest(std::shared_ptr<Request> request) override {
    auto content = T::cast(request->getContent());
    if (content)
      handler(request);
  }

private:
  std::function<void(std::shared_ptr<Request>, T*)> handler;
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
