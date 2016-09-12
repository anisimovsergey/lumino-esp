// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_MESSAGE_HPP
#define CORE_MESSAGE_HPP

#include "IEntity.hpp"
#include "ActionType.hpp"

#include <list>
#include <string>

namespace Core {

class Message : public IEntity {
  TYPE_INFO(Message, IEntity, "message")
  public:
    enum class Priority {High, Mid, Low};

    ActionType      getActionType() const { return actionType; }
    std::string     getResource() const { return resource; }
    void            addTag(std::string tag, std::string value);
    std::string     getTag(std::string tag) const;
    Priority        getPriority() const { return priority; }

  protected:
    Message(ActionType actionType, std::string resource, Priority priority);

  private:
    ActionType actionType;
    std::string resource;
    Priority priority;
    std::list<std::tuple<std::string, std::string>> tags;
};


}

#endif /* end of include guard: CORE_MESSAGE_HPP */
