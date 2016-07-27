// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HPPTTP_SERVER_ASYNC_HPP
#define SERVICES_HPPTTP_SERVER_ASYNC_HPP

#include "IWiFiManager.hpp"
#include "Core/ILoopedService.hpp"

#include <memory>
#include <list>
#include <algorithm>

class AsyncWebServer;
class AsyncWebServerRequest;

namespace Services {

class HttpServerAsync : public Core::ILoopedService {
  TYPE_PTRS(HttpServerAsync)
  public:
    HttpServerAsync(int port,
      std::shared_ptr<const IWiFiManager> wifiManager);
    virtual ~HttpServerAsync();

    void start();

    void loop() override {};

    std::unique_ptr<AsyncWebServer> server;
  private:
    std::shared_ptr<const IWiFiManager> wifiManager;

    String  getLocalDomain();
    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);
};

}

#endif /* end of include guard: SERVICES_HPPTTP_SERVER_ASYNC_HPP */
