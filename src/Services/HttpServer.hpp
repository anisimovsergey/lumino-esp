// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_SERVER_H
#define SERVICES_HTTP_SERVER_H

#include "IHttpServer.hpp"
#include "Controllers/IApiController.hpp"
#include "Json/ISerializationService.hpp"

#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <memory>
#include <list>

namespace Services {

class HttpServer : public IHttpServer {
  public:
    HttpServer(int port,
      std::shared_ptr<const Json::ISerializationService> serializationService);

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

  private:
    std::unique_ptr<AsyncWebServer> server;
    std::list<std::shared_ptr<Controllers::IApiController>> controllers;
    std::shared_ptr<const Json::ISerializationService>  serializationService;

    bool    isIntercepted(AsyncWebServerRequest *request);
    void    redirectToSelf(AsyncWebServerRequest *request);
};

}

#endif /* end of include guard: SERVICES_HTTP_SERVER_H */
