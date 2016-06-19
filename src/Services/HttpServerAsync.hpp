// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_SERVER_ASYNC_H
#define SERVICES_HTTP_SERVER_ASYNC_H

#include "IHttpServer.hpp"
#include "ILoopedService.hpp"

#include "Json/ISerializationService.hpp"
#include "Controllers/IApiController.hpp"

#include <memory>
#include <list>

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

    virtual std::shared_ptr<Core::IActionResult> addGetHandler(
      const String& uri,
      TRequestHandler fn) override;
    virtual std::shared_ptr<Core::IActionResult> addDeleteHandler(
      const String& uri,
      TRequestHandler fn) override;

    virtual std::shared_ptr<Core::IActionResult> addPostHandler(
      const String& uri,
      TRequestWithEntityHandler fn) override;
    virtual std::shared_ptr<Core::IActionResult> addPutHandler(
      const String& uri,
      TRequestWithEntityHandler fn) override;

    virtual void addApiController(
      std::shared_ptr<Controllers::IApiController> controller) override;

    void loop() override {};

  private:
    std::unique_ptr<AsyncWebServer> server;
    std::list<std::shared_ptr<Controllers::IApiController>> controllers;
    std::shared_ptr<const Json::ISerializationService>  serializationService;

    void addHandler(
      const String& uri,
      WebRequestMethod method,
      TRequestHandler fn);

    void addHandler(
      const String& uri,
      WebRequestMethod method,
      TRequestWithEntityHandler fn);

    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);
};

}

#endif /* end of include guard: SERVICES_HTTP_SERVER_ASYNC_H */
