// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_MESSAGE_HPP
#define CORE_I_MESSAGE_HPP

#include "IEntity.hpp"
#include "ActionResult.hpp"

#include <list>
#include <tuple>
#include <memory>

namespace Core {

class ActionType {
public:
  static const ActionType Unknown;
  static const ActionType Get;
  static const ActionType Create;
  static const ActionType Update;
  static const ActionType Delete;

  String  getId() const { return id; }

  bool operator==(const ActionType& other) const {
    return id == other.id;
  }

  bool operator!=(const ActionType& other) const {
    return !(*this == other);
  }

  static ActionType getById(String id) {
    if (id == Get.getId())
      return ActionType::Get;
    if (id == Update.getId())
      return ActionType::Update;
    if (id == Create.getId())
      return ActionType::Create;
    if (id == Delete.getId())
      return ActionType::Delete;
    return ActionType::Unknown;
  }

private:
  ActionType(String id) : id(id) {
  }

  String  id;
};

class Message : public IEntity {
  TYPE_INFO(Message, IEntity, "message")
  public:
    enum class Priority {High, Mid, Low};

    ActionType    getActionType() const { return actionType; }
    String        getResource() const { return resource; }
    void          addTag(String tag, String value);
    String        getTag(String tag) const;
    Priority      getPriority() const { return priority; }

  protected:
    Message(ActionType actionType, String resource, Priority priority);

  private:
    ActionType actionType;
    String resource;
    Priority priority;
    std::list<std::tuple<String, String>> tags;
};

class Request : public Message {
  TYPE_INFO(Request, Message, "request")
  public:
    Request(ActionType actionType, String resource);
    Request(ActionType actionType, String resource,
      IEntity::Unique content);

    const IEntity* getContent() { return content.get(); };

  private:
    IEntity::Unique content;
};

class Response : public Message {
  TYPE_INFO(Response, Message, "response")
  public:
    Response(ActionType actionType, String resource,
      StatusResult::Unique result);

    static Response::Shared createFor(const Request&      request,
                                     StatusResult::Unique result) {
      auto response = std::make_shared<Response>(
             request.getActionType(),
             request.getResource(),
             std::move(result));
      response->addTag("fromClient", request.getTag("fromClient"));
      // TODO: Define sender!
      response->addTag("receiver", request.getTag("sender"));
      return response;
    }

    const StatusResult& getResult() const { return *result; }

  private:
    StatusResult::Unique result;
};

class Notification : public Message {
  TYPE_INFO(Notification, Message, "notification")
  public:
    Notification(ActionType actionType, String resource,
      IEntity::Unique result);

    const IEntity& getResult() const { return *result; };

  private:
    IEntity::Unique result;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_HPP */
