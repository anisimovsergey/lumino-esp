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

class Message : public IEntity {
  TYPE_INFO(IMessage, IEntity, "message")
  public:
    Message(MessageType messageType, String resource);

    MessageType   getMessageType() { return messageType; }
    String        getResource() { return resource; }
    void          addTag(String tag, String value);
    String        getTag(String tag);

  private:
    MessageType messageType;
    String resource;
    std::list<std::tuple<String, String>> tags;
};

class Request : public Message {
  TYPE_INFO(Request, Message, "request")
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
