#include "HttpRequest.hpp"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "Core/Logger.hpp"

using namespace Core;
using namespace Services;

HttpRequest::HttpRequest(
  ESP8266WebServer& server,
  const Json::ISerializationService& serializationService) :
  server(server),
  serializationService(serializationService) {
}

void
HttpRequest::addHeader(const String& header, const String& value) {
  server.sendHeader(header, value);
}

Core::Status
HttpRequest::getJson(std::shared_ptr<IEntity>& entity) {
  String json = server.arg("plain");
  return serializationService.deserialize(json, entity);
}

void
HttpRequest::sendJson(const Status& status) {
  String json;
  serializationService.serialize(status, json);
  int code = status.getCode();
  server.send(code, "text/json", json);
}

void
HttpRequest::sendJson(const IEntity& entity) {
  String json;
  serializationService.serialize(entity, json);
  server.send(200, "text/json", json);
}
