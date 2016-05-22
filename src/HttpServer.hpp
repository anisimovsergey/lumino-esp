
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <WString.h>
#include <memory>

class ESP8266WebServer;

class HttpServer {
  public:
    HttpServer(int port);
    virtual ~HttpServer();

    void begin();
    void loop();
    //void sendError(const Error& error)

  private:
    std::unique_ptr<ESP8266WebServer> server;

    String  getContentType(String filename);
    bool    handleFileRead(String path);
};

#endif /* end of include guard: HTTPSERVER_H */
