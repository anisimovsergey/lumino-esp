// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_SENDER_HPP
#define SERVICES_HTTP_SENDER_HPP

#include "IHttpSender.hpp"
#include "IHttpRequest.hpp"
#include "IHttpResponse.hpp"

namespace Services {

template <class T> class HttpSender : public IHttpSender {
  public:
    virtual void send(
      const Json::ISerializationService& serializationSerivce,
      IHttpRequest& request,
      const Core::IActionResult& actionResult) const override {

      const T& actionResultT = static_cast<const T&>(actionResult);
      auto response = prepareResponse(
        serializationSerivce, request, actionResultT);
      response->send();
    }

  protected:
    virtual std::shared_ptr<IHttpResponse> prepareResponse(
      const Json::ISerializationService& serializationSerivce,
      IHttpRequest& request,
      const T& actionResult) const = 0;
 };

}

#endif /* end of include guard: SERVICES_HTTP_SENDER_HPP */
