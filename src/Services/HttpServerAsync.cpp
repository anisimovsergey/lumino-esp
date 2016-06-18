#include "HttpServerAsync.hpp"

#include "HttpRequest.hpp"

#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

#include <FS.h>

using namespace Core;
using namespace Services;
using namespace Controllers;

HttpServerAsync::HttpServerAsync(
  int port,
  std::shared_ptr<const Json::ISerializationService> serializationService) :
  server(new AsyncWebServer(port)),
  serializationService(serializationService) {
}

//std::shared_ptr<IEntity> entity;
//auto actionResult = request.getJson(entity);
//if (!actionResult->isOk())
//  return actionResult;
/*
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
}*/

HttpServerAsync::~HttpServerAsync() {
}

std::shared_ptr<Core::ActionResult>
HttpServerAsync::addGetHandler(const String& uri, TRequestHandler fn) {
  addHandler(uri, HTTP_GET, fn);
}

std::shared_ptr<Core::ActionResult>
HttpServerAsync::addDeleteHandler(const String& uri, TRequestHandler fn) {
  addHandler(uri, HTTP_DELETE, fn);
}

std::shared_ptr<Core::ActionResult>
HttpServerAsync::addPostHandler(
  const String& uri,
  TRequestWithEntityHandler fn) {

}

std::shared_ptr<Core::ActionResult>
HttpServerAsync::addPutHandler(
  const String& uri,
  TRequestWithEntityHandler fn) {

}

void
HttpServerAsync::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

//Core::Status
//HttpRequest::getJson(std::shared_ptr<IEntity>& entity) {
//  Logger::message("Body: " + body);
//  return serializationService.deserialize(body, entity);
//}

//std::shared_ptr<IHttpResponse>
//HttpRequest::createResponse(const Core::Status& status) {
//    return std::shared_ptr<IHttpResponse>(
//      new HttpResponse(*request.beginResponse(status.getCode())),
//      serializationService
//    )
//}

void
HttpServerAsync::addHandler(
  const String& uri,
  WebRequestMethod method,
  TRequestHandler fn) {
  server->on(uri.c_str(), method, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request);
    auto result = fn(httpRequest);
    // TODO : Send response
  });
}

void
HttpServerAsync::addHandler(
  const String& uri,
  WebRequestMethod method,
  TRequestWithEntityHandler fn) {

  server->on(uri.c_str(), method, [=](AsyncWebServerRequest* request) {
    String body((char*)request->_tempObject);
    std::shared_ptr<IEntity> entity;
    auto result = serializationService->deserialize(body, entity);
    if (!result->isOk())
      ; // TODO Send error back.
    HttpRequest httpRequest(*request);
    result = fn(httpRequest, *entity);
    // TODO : Send response
  }, nullptr, [&](AsyncWebServerRequest *request,
    uint8_t *data, size_t len, size_t index, size_t total){
      if(index == 0)
        request->_tempObject = malloc(total);
      if(request->_tempObject != NULL)
        memcpy((uint8_t*)request->_tempObject+index, data, len);
    }
  );
}

bool
HttpServerAsync::isIntercepted(AsyncWebServerRequest *request) {
  return request->host() != "www.esp8266fs.local";
}

void
HttpServerAsync::redirectToSelf(AsyncWebServerRequest *request) {
  Logger::message("Request redirected");
  AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
  response->addHeader("Location", String("http://") + "www.esp8266fs.local");
  request->send(response);
}

void
HttpServerAsync::start() {
  SPIFFS.begin();
  // Set up static content
  server->serveStatic("", SPIFFS, "");
  server->onNotFound([&](AsyncWebServerRequest *request){
    Logger::message("Request Header:" + request->host() + " Uri:" + request->url());
    if (isIntercepted(request)) {
      redirectToSelf(request);
    } else {
      request->send(404);
    }
  });
  server->begin();
  Logger::message("HTTP asynchronous server started");
}
