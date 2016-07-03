// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HPPTTP_SENDER_HPP
#define SERVICES_HPPTTP_SENDER_HPP

#include "IHttpSender.hpp"
#include "IHttpRequest.hpp"
#include "IHttpResponse.hpp"

namespace Services {

template <class T> class HttpSender : public IHttpSender {
  public:
    // From IHttpSender
    virtual String getTypeId() const override {
      return T::getStaticTypeId();
    }

    virtual std::unique_ptr<Core::StatusResult> getResponse(
      IHttpRequest& request,
      const Core::IActionResult& actionResult,
      std::unique_ptr<IHttpResponse>& response) const override {

      const T& actionResultT = static_cast<const T&>(actionResult);
      return getResponse(request, actionResultT, response);
    }

  protected:
    virtual std::unique_ptr<Core::StatusResult> getResponse(
      IHttpRequest& request,
      const T& value,
      std::unique_ptr<IHttpResponse>& response) const = 0;
 };

}

#endif /* end of include guard: SERVICES_HPPTTP_SENDER_HPP */
