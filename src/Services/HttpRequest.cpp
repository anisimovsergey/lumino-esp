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

void
HttpRequest::addHeader(const String& header, const String& value) {
  //request.addHeader(header, value);
}

Core::Status
HttpRequest::getJson(std::shared_ptr<IEntity>& entity) {
//  String json = request.arg("plain");
//  return serializationService.deserialize(json, entity);
}

void
HttpRequest::sendJson(const Status& status) {
  String json;
  serializationService.serialize(status, json);
  Logger::message("sendJson status: " + json);
  int code = status.getCode();
  auto response = request.beginResponse(code, "text/json", json);
  request.send(response);
}

void
HttpRequest::sendJson(const IEntity& entity) {
  String json;
  serializationService.serialize(entity, json);
  Logger::message("sendJson entity: " + json);    
  auto response = request.beginResponse(200, "text/json", json);
  request.send(response);
}
