// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_SERVER_ASYNC_H
#define SERVICES_HTTP_SERVER_ASYNC_H

#include "ILoopedService.hpp"

#include <memory>
#include <stddef.h>

#include <WString.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

namespace Services {

class HttpServerAsync : public ILoopedService {
  public:
    HttpServerAsync(int port);
    virtual ~HttpServerAsync();

    void start();

    void loop() override {};

  private:
    std::unique_ptr<AsyncWebServer> server;

    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);
};

}

#endif /* end of include guard: SERVICES_HTTP_SERVER_ASYNC_H */
