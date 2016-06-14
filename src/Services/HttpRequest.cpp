#include "HttpRequest.hpp"

#include <ESPAsyncWebServer.h>

#include "Core/Logger.hpp"

using namespace Core;
using namespace Services;

HttpRequest::HttpRequest(
  AsyncWebServerRequest& request,
  const Json::ISerializationService& serializationService) :
  request(request),
  serializationService(serializationService) {
}

HttpRequest::~HttpRequest() {
}

void
HttpRequest::addHeader(const String& header, const String& value) {
  //request.sendHeader(header, value);
}

Core::Status
HttpRequest::getJson(std::shared_ptr<IEntity>& entity) {
  String json = request.arg("plain");
  return serializationService.deserialize(json, entity);
}

void
HttpRequest::sendJson(const Status& status) {
  String json;
  Logger::message("sendJson status");
  serializationService.serialize(status, json);
  int code = status.getCode();
  Logger::message(json);
  request.send(code, "text/json", json);
}

void
HttpRequest::sendJson(const IEntity& entity) {
  String json;
  Logger::message("sendJson entity");
  auto status = serializationService.serialize(entity, json);
  if (!status.isOk()) {
    sendJson(status);
    return;
  }
  Logger::message(json);
  request.send(200, "text/json", json);
}
