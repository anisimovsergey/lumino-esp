// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HPPTTP_REQEST_HPP
#define SERVICES_HPPTTP_REQEST_HPP

#include "IHttpRequest.hpp"

class AsyncWebServerRequest;

namespace Services {

class HttpRequest : public IHttpRequest {
  public:
    HttpRequest(AsyncWebServerRequest& request);

    virtual String getArgument(String argument) override;

    virtual String getHeader(String header) override;

    virtual std::unique_ptr<IHttpResponse>createResponse(
        int code) override;

    virtual std::unique_ptr<IHttpResponse>createResponse(
        int code,
        String contentType,
        String content) override;

  private:
    AsyncWebServerRequest& request;
};

}

#endif /* end of include guard: SERVICES_HPPTTP_REQEST_HPP */
