// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTP_RESPONSE_H
#define SERVICES_I_HTTP_RESPONSE_H

#include "Core/Status.hpp"
#include "Core/IEntity.hpp"

#include <WString.h>

namespace Services {

class IHttpResponse {
  public:
    virtual void setLocation(const String& value) = 0;
    virtual void sendJson(const Core::Status& status) = 0;
    virtual void sendJson(const Core::IEntity& entity) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTP_RESPONSE_H */
