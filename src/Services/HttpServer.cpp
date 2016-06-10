#include "HttpServer.hpp"

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
  server->on(uri.c_str(), HTTP_GET, [&](AsyncWebServerRequest *request){
    fn();
  });
}

void
HttpServer::addPutHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_PUT, [&](AsyncWebServerRequest *request){
    fn();
  });
}

void
HttpServer::addPostHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_POST, [&](AsyncWebServerRequest *request){
    fn();
  });
}

void
HttpServer::addDeleteHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_DELETE, [&](AsyncWebServerRequest *request){
    fn();
  });
}

void
HttpServer::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

void
HttpServer::setLocation(const String& location) {
  //server->sendHeader("Location", location);
}

Core::Status
HttpServer::getJson(std::shared_ptr<Core::IEntity>& entity) {
  //String json = server->arg("plain");
  //return serializationService->deserialize(json, entity);
}

void
HttpServer::sendJson(const Core::Status& status) {
  //String json;
  //serializationService->serialize(status, json);
  //int code = status.getCode();
  //server->send(code, "text/json", json);
}

void
HttpServer::sendJson(const Core::IEntity& entity) {
  //String json;
  //serializationService->serialize(entity, json);
  //server->send(200, "text/json", json);
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
  Logger::message("HTTP server started");
  SPIFFS.begin();
  server->serveStatic("", SPIFFS, "");

  // Setting up "File not found" (404) responce
  server->onNotFound([&](AsyncWebServerRequest *request){
    Logger::message("Request Header:" + request->host() + " Uri:" + request->url());
    if (isIntercepted(request)) {
      redirectToSelf(request);
    } else {
      request->send(404);
    }
  });
  server->begin();
}
