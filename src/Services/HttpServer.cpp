#include "HttpServer.hpp"

#include "HttpRequest.hpp"

#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

#include <FS.h>
#include <WiFiServer.h>
#include <WiFiClient.h>

using namespace Core;
using namespace Services;
using namespace Controllers;

HttpServer::HttpServer(
  int port,
  std::shared_ptr<const Json::ISerializationService> serializationService) :
  server(new AsyncWebServer(port)),
  serializationService(serializationService) {
}

void
HttpServer::addGetHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_GET, [&](AsyncWebServerRequest *asyncRequest){
    HttpRequest request(*asyncRequest, *serializationService);
    fn(request);
  });
}

void
HttpServer::addPutHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_PUT, [&](AsyncWebServerRequest *asyncRequest){
    HttpRequest request(*asyncRequest, *serializationService);
    fn(request);
  });
}

void
HttpServer::addPostHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_POST, [&](AsyncWebServerRequest *asyncRequest){
    HttpRequest request(*asyncRequest, *serializationService);
    fn(request);
  });
}

void
HttpServer::addDeleteHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_DELETE, [&](AsyncWebServerRequest *asyncRequest){
    HttpRequest request(*asyncRequest, *serializationService);
    fn(request);
  });
}

void
HttpServer::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

bool
HttpServer::isIntercepted(AsyncWebServerRequest *request) {
  return request->host() != "www.esp8266fs.local";
}

void
HttpServer::redirectToSelf(AsyncWebServerRequest *request) {
  Logger::message("Request redirected");
  AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
  response->addHeader("Location", String("http://") + "www.esp8266fs.local");
  request->send(response);
}

void
HttpServer::start() {
  SPIFFS.begin();
  server->serveStatic("", SPIFFS, "");
  server->onNotFound([&](AsyncWebServerRequest *request){
    Logger::message("Request Header:" + request->host() + " Uri:" + request->url());
    if (isIntercepted(request)) {
      redirectToSelf(request);
    } else {
      request->send(404);
    }
  });
  server->begin();
  Logger::message("HTTP server started");
}
