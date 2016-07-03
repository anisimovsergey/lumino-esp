// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HPPTTP_RESPONSE_HPP
#define SERVICES_HPPTTP_RESPONSE_HPP

#include "IHttpResponse.hpp"

class AsyncWebServerRequest;
class AsyncWebServerResponse;

namespace Services {

class HttpResponse : public IHttpResponse {
  public:
    HttpResponse(
      AsyncWebServerRequest& request,
      AsyncWebServerResponse& response);

    virtual void setHeader(String header, String value) override;
    virtual void send() override;

  private:
    AsyncWebServerRequest& request;
    AsyncWebServerResponse& response;
};

}

#endif /* end of include guard: SERVICES_HPPTTP_RESPONSE_HPP */
