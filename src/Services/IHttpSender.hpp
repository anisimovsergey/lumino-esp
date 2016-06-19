// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_HTTP_SENDER_H
#define JSON_I_HTTP_SENDER_H

#include "Core/ActionResult.hpp"
#include "Json/ISerializationService.hpp"
#include "IHttpRequest.hpp"

namespace Services {

class IHttpSender {
  public:
    virtual ~IHttpSender() {};

    virtual void send(
      const Json::ISerializationService& serializationSerivce,
      IHttpRequest& request,
      const Core::IActionResult& actionResult) const = 0;

    virtual String getTypeId() const = 0;
};

}

#endif /* end of include guard: JSON_I_SERIALIZER_H */
