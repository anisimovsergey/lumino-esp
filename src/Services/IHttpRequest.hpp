// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTP_REQEST_H
#define SERVICES_I_HTTP_REQEST_H

#include "Core/IEntity.hpp"

#include <WString.h>

#include <memory>

namespace Services {

class IHttpRequest {
  public:
    virtual String getArgument(String parameter) = 0;
    virtual String getHeader(String header) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTP_REQEST_H */
