#include "HttpResponse.hpp"

#include "Core/Logger.hpp"

#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpResponse::HttpResponse(
  AsyncWebServerRequest& request,
  AsyncWebServerResponse& response) :
  request(request), response(response) {
}

void
HttpResponse::setHeader(String header, String value) {
  response.addHeader(header, value);
}

void
HttpResponse::send() {
  request.send(&response);
}
