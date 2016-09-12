// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_NOTIFICATION_HPP
#define CORE_NOTIFICATION_HPP

#include "Message.hpp"

namespace Core {

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

#endif /* end of include guard: CORE_NOTIFICATION_HPP */
