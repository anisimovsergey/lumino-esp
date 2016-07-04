// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_MESSAGE_QUEUE_HPP
#define CORE_I_MESSAGE_QUEUE_HPP

#include "ILoopedService.hpp"

#include <WString.h>

#include <functional>

namespace Core {

class IMessageQueue : public ILoopedService {
  public:
    virtual ~IMessageQueue();
    
    typedef std::function<void()> TAction;
    virtual void post(TAction action) = 0;
};

}

#endif /* end of include guard: CORE_I_MESSAGE_QUEUE_HPP */
