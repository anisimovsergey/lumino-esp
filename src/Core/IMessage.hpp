// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_MESSAGE_HPP
#define CORE_I_MESSAGE_HPP

#include "IEntity.hpp"

namespace Core {

class IMessage : public IEntity {
  public:
    virtual ~IMessage();

};

}

#endif /* end of include guard: CORE_I_MESSAGE_HPP */
