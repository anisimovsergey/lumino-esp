#include "HttpRequest.hpp"

#include "Core/Logger.hpp"

#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpRequest::HttpRequest(
  AsyncWebServerRequest& request) :
  request(request) {
}

HttpRequest::~HttpRequest() {
}

String
HttpRequest::getArgument(String argument) {
  return request.arg(argument.c_str());
}

String
HttpRequest::getHeader(String header) {
  return request.header(header.c_str());
}
