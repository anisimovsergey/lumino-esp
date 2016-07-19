// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HPPTTP_SERVER_ASYNC_HPP
#define SERVICES_HPPTTP_SERVER_ASYNC_HPP

#include "IHttpServer.hpp"
#include "IHttpController.hpp"
#include "IWiFiManager.hpp"
#include "Core/ILoopedService.hpp"
#include "Json/ISerializationService.hpp"

#include <memory>
#include <list>
#include <algorithm>

class AsyncWebServer;
class AsyncWebServerRequest;

namespace Services {

class HttpServerAsync : public IHttpServer, public Core::ILoopedService {
  public:
    HttpServerAsync(int port,
      std::shared_ptr<const Json::ISerializationService> serializationService,
      std::shared_ptr<const IWiFiManager> wifiManager);
    virtual ~HttpServerAsync();

    void start();

    virtual void addGetHandler(
      const String& uri,
      TRequestHandler requestHandler) override;

    virtual void addDeleteHandler(
      const String& uri,
      TRequestHandler requestHandler) override;

    virtual void addPostHandler(
      const String& uri,
      TRequestWithEntityHandler requestHandler) override;

    virtual void addPutHandler(
      const String& uri,
      TRequestWithEntityHandler requestHandler) override;

    virtual void addApiController(
      std::shared_ptr<IHttpController> controller) override;

    virtual void addHttpSender(
      std::shared_ptr<IHttpSender> httpSender) override;

    void loop() override {};


    std::unique_ptr<AsyncWebServer> server;
  private:    
    std::list<std::shared_ptr<IHttpController>> controllers;
    std::list<std::shared_ptr<IHttpSender>> senders;
    std::shared_ptr<const Json::ISerializationService>  serializationService;
    std::shared_ptr<const IWiFiManager> wifiManager;

    void addHandler(
      const String& uri,
      int method,
      TRequestHandler requestHandler);

    void addHandler(
      const String& uri,
      int method,
      TRequestWithEntityHandler requestHandler);

    void sendResponse(
      IHttpRequest& request,
      const Core::IActionResult& actionResult);

    std::shared_ptr<IHttpSender> getSender(String typeId) const;
    String  getLocalDomain();
    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);
};

}

#endif /* end of include guard: SERVICES_HPPTTP_SERVER_ASYNC_HPP */
