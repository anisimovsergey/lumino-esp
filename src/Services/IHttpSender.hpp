// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTP_SENDER_H
#define SERVICES_I_HTTP_SENDER_H

#include "Core/ActionResult.hpp"
#include "Json/ISerializationService.hpp"
#include "IHttpRequest.hpp"

namespace Services {

class IHttpSender {
  public:
    virtual ~IHttpSender() {};

    virtual void send(
      IHttpRequest& request,
      const Core::IActionResult& actionResult) const = 0;

    virtual String getTypeId() const = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTP_SENDER_H */
