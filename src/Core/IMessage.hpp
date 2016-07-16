// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_MESSAGE_HPP
#define CORE_I_MESSAGE_HPP

#include "IEntity.hpp"
#include "ActionResult.hpp"

namespace Core {

class MessageType {

  static const MessageType Get;
  static const MessageType Create;
  static const MessageType Update;
  static const MessageType Delete;

  String  getId() const { return id; }

  bool operator==(const MessageType& other) const {
    return id == other.id;
  }

  bool operator!=(const MessageType& other) const {
    return !(*this == other);
  }

private:
  MessageType(String id) : id(id) {
  }

  String  id;
};

class IMessage : public IEntity {
  public:
    virtual ~IMessage();

    MessageType getMessageType();
    String getResource();
    String getTag(String tag);
};

class Request : public IMessage {
  public:
    const IEntity& getContent();
};
/*
class Response : public IMessage {
  public:
    const IActionResult& getResult();
};

class Notification : public IMessage {
  public:
    const IActionResult& getResult();
};
*/
}

#endif /* end of include guard: CORE_I_MESSAGE_HPP */
