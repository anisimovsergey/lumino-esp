// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTPSERVER_H
#define SERVICES_HTTPSERVER_H

#include "IStatusCodeRegistry.hpp"
#include "IHttpServer.hpp"
#include <WString.h>
#include <memory>

class ESP8266WebServer;

namespace Services {

class HttpServer : public IHttpServer {
  public:
    HttpServer(int port, const IStatusCodeRegistry& registry);

    void start();
    void loop();

    virtual void addGetHandler(const String& uri,
                               THandlerFunction fn) override;
    virtual void addPutHandler(const String& uri,
                               THandlerFunction fn) override;

    virtual void sendJson(const Core::Status& status) override;
    virtual void sendJson(const Core::IEntity& value) override;

  private:
    std::unique_ptr<ESP8266WebServer> server;
    const IStatusCodeRegistry&  registry;

    String  getContentType(String filename);
    bool    handleFileRead(String path);
};

}

#endif /* end of include guard: SERVICES_HTTPSERVER_H */
