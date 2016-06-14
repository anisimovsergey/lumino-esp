// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_SERVER_SYNC_H
#define SERVICES_HTTP_SERVER_SYNC_H

#include "IHttpServer.hpp"
#include "ILoopedService.hpp"

#include "Json/ISerializationService.hpp"
#include "Controllers/IApiController.hpp"

#include <memory>
#include <list>

class ESP8266WebServer;

namespace Services {

class HttpServerSync : public IHttpServer, public ILoopedService {
  public:
    HttpServerSync(int port,
      std::shared_ptr<const Json::ISerializationService> serializationService);
    virtual ~HttpServerSync();

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

    void loop() override;

  private:
    std::unique_ptr<ESP8266WebServer> server;
    std::list<std::shared_ptr<Controllers::IApiController>> controllers;
    std::shared_ptr<const Json::ISerializationService>  serializationService;
};

}

#endif /* end of include guard: SERVICES_HTTP_SERVER_SYNC_H */
