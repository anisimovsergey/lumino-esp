
#include "HttpServer.hpp"

#include "Core/Logger.hpp"

#include <FS.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

using namespace Core;
using namespace Services;
using namespace Controllers;

HttpServer::HttpServer(
  int port,
  std::shared_ptr<const IStatusCodeRegistry> registry,
  std::shared_ptr<const Json::ISerializationService> serializationService) :
  server(new ESP8266WebServer(port)),
  registry(registry),
  serializationService(serializationService) {
}

String
HttpServer::getContentType(String filename) {
  if(server->hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool
HttpServer::handleFileRead(String path) {

  if (path.endsWith("/"))
    path += "index.html";

  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){

    String contentType = getContentType(path);
    if(SPIFFS.exists(pathWithGz))
      path = pathWithGz;

    File file = SPIFFS.open(path, "r");
    server->streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
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
HttpServer::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

void
HttpServer::sendJson(const Core::Status& status) {
  Logger::message("Serializing status """ + status.getCode() + """");
  String json = serializationService->serialize(status);
  int code = registry->getCode(status);
  Logger::message("Sending status with code """ + String(code) + """");
  server->send(code, "text/json", json);
}

void
HttpServer::sendJson(const Core::IEntity& entity) {
  Logger::message("Serializing entity of type """ + entity.getTypeId() + """");
  String json = serializationService->serialize(entity);
  Logger::message("Sending entity of type """ + entity.getTypeId() + """");
  server->send(200, "text/json", json);
}

void
HttpServer::start() {
  SPIFFS.begin();
  // Setting up "File not found" (404) responce
  server->onNotFound([&](){
    if(!handleFileRead(server->uri()))
      server->send(404, "text/plain", "FileNotFound");
  });
  server->begin();
}

void
HttpServer::loop() {
  server->handleClient();
}
