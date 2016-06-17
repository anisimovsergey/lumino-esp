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

    virtual void addGetHandler(
      const String& uri,
      THandlerFunction fn) override;
    virtual void addPutHandler(
      const String& uri,
      THandlerFunction fn) override;
    virtual void addPostHandler(
      const String& uri,
      THandlerFunction fn) override;
    virtual void addDeleteHandler(
      const String& uri,
      THandlerFunction fn) override;

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
      THandlerFunction fn);
    
    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);
};

}

#endif /* end of include guard: SERVICES_HTTP_SERVER_ASYNC_H */
