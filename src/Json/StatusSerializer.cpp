#include "StatusSerializer.hpp"

using namespace Json;
using namespace Core;

/*
void
HttpServer::sendError(const Error& error) {
  String json = "{";
  json += "\"type\": \"error\",";
  json += "\"status\": \"500\",";
  json += "\"code\": \"UnableToScanWiFiNetwors\",";
  json += "\"title\": \"Unable to scan WiFi networks.\",";
  json += "}";
  server->send(500, "text/json", json);
}*/

void
StatusSerializer::serialize(const Status& status,
                            ISerializationContext& context) {
  context.setType("status");
  context.setValue("code", status.getCode());
  context.setValue("title", status.getTitle());
}
