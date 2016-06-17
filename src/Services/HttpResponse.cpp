#include "HttpResponse.hpp"

#include <ESPAsyncWebServer.h>

#include "Core/Logger.hpp"

using namespace Core;
using namespace Services;

HttpResponse::HttpResponse(
  AsyncWebServerResponse& response,
  const Json::ISerializationService& serializationService) :
  response(response),
  serializationService(serializationService) {
}

HttpResponse::~HttpResponse() {
}

void
HttpResponse::setLocation(const String& location) {
  response.addHeader("Location", location);
}

void
HttpResponse::sendJson(const Status& status) {
  String json;
  Logger::message("sendJson status");
  serializationService.serialize(status, json);
  int code = status.getCode();
  Logger::message(json);
  response.send(code, "text/json", json);
}

void
HttpResponse::sendJson(const IEntity& entity) {
  String json;
  Logger::message("sendJson entity");
  auto status = serializationService.serialize(entity, json);
  if (!status.isOk()) {
    sendJson(status);
    return;
  }
  Logger::message(json);
  response.send(200, "text/json", json);
}
