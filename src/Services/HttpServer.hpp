
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <WString.h>
#include <memory>
#include "IHttpServer.hpp"

class ESP8266WebServer;

class HttpServer : public IHttpServer {
  public:
    HttpServer(int port);

    void start();
    void loop();

    virtual void addGetHandler(const char* uri, THandlerFunction fn) override;
    virtual void addPutHandler(const char* uri, THandlerFunction fn) override;

  private:
    std::unique_ptr<ESP8266WebServer> server;

    String  getContentType(String filename);
    bool    handleFileRead(String path);
};

#endif /* end of include guard: HTTPSERVER_H */
