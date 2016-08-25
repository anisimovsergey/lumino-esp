// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_MESSAGE_HPP
#define CORE_I_MESSAGE_HPP

#include "IEntity.hpp"
#include "ActionResult.hpp"

#include "WString.h"
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

  std::string  getId() const { return id; }

  bool operator==(const ActionType& other) const {
    return id == other.id;
  }

  bool operator!=(const ActionType& other) const {
    return !(*this == other);
  }

  static ActionType getById(std::string id) {
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
  ActionType(const std::string& id) : id(id) {
  }

  std::string  id;
};

class Message : public IEntity {
  TYPE_INFO(Message, IEntity, "message")
  public:
    enum class Priority {High, Mid, Low};

    ActionType    getActionType() const { return actionType; }
    std::string        getResource() const { return resource; }
    void          addTag(std::string tag, std::string value);
    std::string        getTag(std::string tag) const;
    Priority      getPriority() const { return priority; }

  protected:
    Message(ActionType actionType, std::string resource, Priority priority);

  private:
    ActionType actionType;
    std::string resource;
    Priority priority;
    std::list<std::tuple<std::string, std::string>> tags;
};

class Request : public Message {
  TYPE_INFO(Request, Message, "request")
  public:
    Request(ActionType actionType, std::string resource);
    Request(ActionType actionType, std::string resource,
      IEntity::Unique content);

    const IEntity* getContent() const { return content.get(); };

  private:
    IEntity::Unique content;
};

class Response : public Message {
  TYPE_INFO(Response, Message, "response")
  public:
    Response(ActionType actionType, std::string resource,
      ActionResult::Unique result);

    const ActionResult& getResult() const { return *result; }

  private:
    ActionResult::Unique result;
};

class Notification : public Message {
  TYPE_INFO(Notification, Message, "notification")
  public:
    Notification(ActionType actionType, std::string resource,
      IEntity::Unique result);

    const IEntity* getContent() const { return result.get(); };

  private:
    IEntity::Unique result;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_HPP */
