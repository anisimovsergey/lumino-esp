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
  server(new ESP8266WebServer(port)),
  serializationService(serializationService) {
}

void
HttpServer::addGetHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_GET, fn);
}

void
HttpServer::addPutHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_PUT, fn);
}

void
HttpServer::addPostHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_POST, fn);
}

void
HttpServer::addDeleteHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_DELETE, fn);
}

void
HttpServer::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

void
HttpServer::setLocation(const String& location) {
  server->sendHeader("Location", location);
}

Core::Status
HttpServer::getJson(std::shared_ptr<Core::IEntity>& entity) {
  String json = server->arg("plain");
  return serializationService->deserialize(json, entity);
}

void
HttpServer::sendJson(const Core::Status& status) {
  String json;
  serializationService->serialize(status, json);
  int code = status.getCode();
  server->send(code, "text/json", json);
}

void
HttpServer::sendJson(const Core::IEntity& entity) {
  String json;
  serializationService->serialize(entity, json);
  server->send(200, "text/json", json);
}

bool
HttpServer::isIntercepted() {
  return server->hostHeader() != "esp8266fs.local";
}

void
HttpServer::redirectToSelf() {
  Logger::message("Request redirected");
  server->sendHeader("Location", String("http://") + "esp8266fs.local");
  server->send(302, "text/plain", "");
  server->client().stop();
}

void
HttpServer::start() {
  Logger::message("HTTP server started");
  SPIFFS.begin();
  server->serveStatic("", SPIFFS, "");

  // Setting up "File not found" (404) responce
  server->onNotFound([&](){
    Logger::message("Request Header:" + server->hostHeader() + " Uri:" + server->uri());
    if (isIntercepted()) {
      redirectToSelf();
    } else {
      server->send(404, "text/plain", "FileNotFound");
    }
  });
  server->begin();
}

void
HttpServer::loop() {
  server->handleClient();
}
