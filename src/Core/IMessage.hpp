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
    ActionType    getActionType() const { return actionType; }
    String        getResource() const { return resource; }
    void          addTag(String tag, String value);
    String        getTag(String tag) const;

  protected:
    Message(ActionType actionType, String resource);

  private:
    ActionType actionType;
    String resource;
    std::list<std::tuple<String, String>> tags;
};

class Request : public Message {
  TYPE_INFO(Request, Message, "request")
  public:
    Request(ActionType actionType, String resource,
      std::unique_ptr<IEntity> content);

    const IEntity* getContent() { return content.get(); };

  private:
    std::unique_ptr<IEntity> content;
};

class Response : public Message {
  TYPE_INFO(Response, Message, "response")
  public:
    Response(ActionType actionType, String resource,
      std::unique_ptr<StatusResult> result);

    const StatusResult& getResult() const { return *result; }

  private:
    std::unique_ptr<StatusResult> result;
};

class Notification : public Message {
  TYPE_INFO(Notification, Message, "notification")
  public:
    Notification(ActionType actionType, String resource,
      std::unique_ptr<IEntity> result);

    const IEntity* getResult() { return result.get(); };

  private:
    std::unique_ptr<IEntity> result;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_HPP */
