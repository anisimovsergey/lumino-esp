// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HPPTTP_SENDER_HPP
#define SERVICES_I_HPPTTP_SENDER_HPP

#include "Core/ActionResult.hpp"
#include "Json/ISerializationService.hpp"
#include "IHttpRequest.hpp"

namespace Services {

class IHttpSender {
  public:
    virtual ~IHttpSender();

    virtual String getTypeId() const = 0;

    virtual std::unique_ptr<Core::StatusResult> getResponse(
      IHttpRequest& request,
      const Core::IActionResult& actionResult,
      std::unique_ptr<IHttpResponse>& response) const = 0;
};

}

#endif /* end of include guard: SERVICES_I_HPPTTP_SENDER_HPP */
