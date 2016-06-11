// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTP_REQEST_H
#define SERVICES_I_HTTP_REQEST_H

#include "Core/Status.hpp"
#include "Core/IEntity.hpp"

#include <WString.h>

#include <memory>

namespace Services {

class IHttpRequest {
  public:
    virtual void addHeader(const String& header, const String& value) = 0;

    virtual Core::Status getJson(
      std::shared_ptr<Core::IEntity>& entity) = 0;

    virtual void sendJson(const Core::Status& status) = 0;
    virtual void sendJson(const Core::IEntity& entity) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTP_REQEST_H */
