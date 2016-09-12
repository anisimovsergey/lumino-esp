// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_REQUEST_HPP
#define CORE_REQUEST_HPP

#include "Message.hpp"

namespace Core {

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

}

#endif /* end of include guard: CORE_MESSAGE_HPP */