#include "HttpRequest.hpp"

#include "HttpResponse.hpp"
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

std::shared_ptr<IHttpResponse>
HttpRequest::createResponse(int code) {
  auto response = request.beginResponse(code);
  return std::make_shared<HttpResponse>(request, *response);
}

std::shared_ptr<IHttpResponse>
HttpRequest::createResponse(
  int code, String contentType, String content) {
  auto response = request.beginResponse(code, contentType, content);
  return std::make_shared<HttpResponse>(request, *response);
}
