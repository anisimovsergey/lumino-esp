// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_REQEST_H
#define SERVICES_HTTP_REQEST_H

#include "IHttpRequest.hpp"

class AsyncWebServerRequest;

namespace Services {

class HttpRequest : public IHttpRequest {
  public:
    HttpRequest(AsyncWebServerRequest& request);
    virtual ~HttpRequest();

    virtual String getArgument(String argument) override;
    virtual String getHeader(String header) override;
    virtual std::shared_ptr<IHttpResponse> createResponse(
      int code, String contentType, String content) override;

  private:
    AsyncWebServerRequest& request;
};

}

#endif /* end of include guard: SERVICES_HTTP_REQEST_H */
