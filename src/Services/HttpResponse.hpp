// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_RESPONSE_H
#define SERVICES_HTTP_RESPONSE_H

#include "IHttpResponse.hpp"

class AsyncWebServerRequest;
class AsyncWebServerResponse;

namespace Services {

class HttpResponse : public IHttpResponse {
  public:
    HttpResponse(
      AsyncWebServerRequest& request,
      AsyncWebServerResponse& response);
    virtual ~HttpResponse();

    virtual void setHeader(String header, String value) override;
    virtual void send() override;

  private:
    AsyncWebServerRequest& request;
    AsyncWebServerResponse& response;
};

}

#endif /* end of include guard: SERVICES_HTTP_RESPONSE_H */
