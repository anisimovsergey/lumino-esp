// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTPSERVER_H
#define SERVICES_HTTPSERVER_H

#include "IHttpServer.hpp"
#include <WString.h>
#include <memory>

class ESP8266WebServer;

namespace Services {

class HttpServer : public IHttpServer {
  public:
    HttpServer(int port);

    void start();
    void loop();

    virtual void addGetHandler(const char* uri,
                               THandlerFunction fn) override;
    virtual void addPutHandler(const char* uri,
                               THandlerFunction fn) override;

    virtual void sendJson(const Core::ISerializable& value) override;

  private:
    std::unique_ptr<ESP8266WebServer> server;

    String  getContentType(String filename);
    bool    handleFileRead(String path);
};

}

#endif /* end of include guard: SERVICES_HTTPSERVER_H */
