#include "HttpServerSync.hpp"

#include "HttpRequest.hpp"

#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

#include <WiFiServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

using namespace Core;
using namespace Services;
using namespace Controllers;

HttpServerSync::HttpServerSync(
  int port,
  std::shared_ptr<const Json::ISerializationService> serializationService) :
  server(new ESP8266WebServer(port)),
  serializationService(serializationService) {
}

HttpServerSync::~HttpServerSync() {

}

void
HttpServerSync::addGetHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_GET, [=](void){
    HttpRequest request(*server.get(), *serializationService);
    fn(request);
  });
}

void
HttpServerSync::addPutHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_PUT, [=](void){
    //HttpRequest request(*asyncRequest, *serializationService);
    //fn(request);
  });
}

void
HttpServerSync::addPostHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_POST, [=](void){
    //HttpRequest request(*asyncRequest, *serializationService);
    //fn(request);
  });
}

void
HttpServerSync::addDeleteHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_DELETE, [=](void){
    //HttpRequest request(*asyncRequest, *serializationService);
    //fn(request);
  });
}

void
HttpServerSync::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

void
HttpServerSync::start() {
  server->onNotFound([&](void){
    server->send(404);
  });
  server->begin();
  Logger::message("HTTP syncronous server started");
}

void
HttpServerSync::loop() {
  server->handleClient();
}
