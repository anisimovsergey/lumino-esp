// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HPPTTP_SERVER_ASYNC_HPP
#define SERVICES_HPPTTP_SERVER_ASYNC_HPP

#include "IHttpServer.hpp"
#include "IHttpController.hpp"
#include "ILoopedService.hpp"

#include "Json/ISerializationService.hpp"

#include <memory>
#include <list>
#include <algorithm>

#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

namespace Services {

class HttpServerAsync : public IHttpServer, public ILoopedService {
  public:
    HttpServerAsync(int port,
      std::shared_ptr<const Json::ISerializationService> serializationService);
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

  private:
    std::unique_ptr<AsyncWebServer> server;
    std::list<std::shared_ptr<IHttpController>> controllers;
    std::list<std::shared_ptr<IHttpSender>> senders;
    std::shared_ptr<const Json::ISerializationService>  serializationService;

    void addHandler(
      const String& uri,
      WebRequestMethod method,
      TRequestHandler requestHandler);

    void addHandler(
      const String& uri,
      WebRequestMethod method,
      TRequestWithEntityHandler requestHandler);

    void sendResponse(
      IHttpRequest& request,
      std::shared_ptr<Core::IActionResult> result);

    std::shared_ptr<IHttpSender> getSender(String typeId) const;

    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);
};

}

#endif /* end of include guard: SERVICES_HPPTTP_SERVER_ASYNC_HPP */
