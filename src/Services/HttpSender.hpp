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
    String getTypeId() const override {
      return T::getStaticTypeId();
    }

    virtual void send(
      IHttpRequest& request,
      const Core::IActionResult& actionResult) const override {

      const T& actionResultT = static_cast<const T&>(actionResult);
      auto response = prepareResponse(request, actionResultT);
      response->send();
    }

  protected:
    virtual std::shared_ptr<IHttpResponse> prepareResponse(
      IHttpRequest& request,
      const T& actionResult) const = 0;
 };

}

#endif /* end of include guard: SERVICES_HPPTTP_SENDER_HPP */
