#include "HttpRequest.hpp"

#include "HttpResponse.hpp"

#include "Core/Logger.hpp"

#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpRequest::HttpRequest(
  AsyncWebServerRequest& request,
  const String& body,
  const Json::ISerializationService& serializationService) :
  request(request),
  body(body),
  serializationService(serializationService) {
}

HttpRequest::~HttpRequest() {
}

Core::Status
HttpRequest::getJson(std::shared_ptr<IEntity>& entity) {
  Logger::message("Body: " + body);
  return serializationService.deserialize(body, entity);
}

std::shared_ptr<IHttpResponse>
HttpRequest::createResponse(const Core::Status& status) {
    return std::shared_ptr<IHttpResponse>(
      new HttpResponse(*request.beginResponse(status.getCode())),
      serializationService
    )
}
