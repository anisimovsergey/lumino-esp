#include "HttpServerAsync.hpp"
#include "HttpRequest.hpp"

#include "Core/Utils.hpp"

#include <Hash.h>
#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpServerAsync::HttpServerAsync(
  int port,
  std::shared_ptr<const Json::ISerializationService> serializationService) :
  server(make_unique<AsyncWebServer>(port)),
  serializationService(serializationService) {
}

HttpServerAsync::~HttpServerAsync() {
}

void
HttpServerAsync::addGetHandler(
  const String& uri,
  TRequestHandler requestHandler) {
  addHandler(uri, HTTP_GET, requestHandler);
}

void
HttpServerAsync::addDeleteHandler(
  const String& uri,
  TRequestHandler requestHandler) {
  addHandler(uri, HTTP_DELETE, requestHandler);
}

void
HttpServerAsync::addPostHandler(
  const String& uri,
  TRequestWithEntityHandler requestHandler) {
  addHandler(uri, HTTP_POST, requestHandler);
}

void
HttpServerAsync::addPutHandler(
  const String& uri,
  TRequestWithEntityHandler requestHandler) {
  addHandler(uri, HTTP_PUT, requestHandler);
}

void
HttpServerAsync::addApiController(
  std::shared_ptr<IHttpController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

void
HttpServerAsync::addHttpSender(
  std::shared_ptr<IHttpSender> httpSender) {
  senders.push_back(httpSender);
}

void
HttpServerAsync::addHandler(
  const String& uri,
  int method,
  TRequestHandler requestHandler) {
  server->on(uri.c_str(), (WebRequestMethod)method, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request);
    auto actionResult = requestHandler(httpRequest);
    sendResponse(httpRequest, *actionResult);
  });
}

void
HttpServerAsync::addHandler(
  const String& uri,
  int method,
  TRequestWithEntityHandler requestHandler) {

  server->on(uri.c_str(), (WebRequestMethod)method,
    [=](AsyncWebServerRequest* request) {
    String body((char*)request->_tempObject);
    HttpRequest httpRequest(*request);
    std::unique_ptr<IEntity> entity;
    auto statusResult = serializationService->deserialize(body, entity);
    if (!statusResult->isOk()) {
      sendResponse(httpRequest, *statusResult);
      return;
    }
    auto actionResult = requestHandler(httpRequest, *entity);
    sendResponse(httpRequest, *actionResult);
  }, nullptr, [&](AsyncWebServerRequest *request,
                  uint8_t *data, size_t len, size_t index, size_t total){
      if (index == 0) {
        request->_tempObject = malloc(total + 1);
        *((uint8_t*)request->_tempObject + total) = '\0';
      }
      if(request->_tempObject != nullptr) {
        memcpy((uint8_t*)request->_tempObject+index, data, len);
      }
    }
  );
}

void
HttpServerAsync::sendResponse(
  IHttpRequest& request,
  const IActionResult& result) {

  String typeId = result.getTypeId();
  std::unique_ptr<IHttpResponse> response;
  auto sender = getSender(typeId);
  if (sender) {
      auto actionResult = sender->getResponse(request, result, response);
      if (!actionResult->isOk())
          sender->getResponse(request, result, response);
  } else {
      response = request.createResponse(StatusCode::InternalServerError.getCode());
  }
  if (response)
    response->send();
}

std::shared_ptr<IHttpSender>
HttpServerAsync::getSender(String typeId) const {

  auto findIter = std::find_if(senders.begin(), senders.end(),
    [&](std::shared_ptr<const IHttpSender> sender){
      return sender->getTypeId() == typeId;
    });

  if (findIter == senders.end())
    return nullptr;

  return *findIter;
}

bool
HttpServerAsync::isIntercepted(AsyncWebServerRequest *request) {
  return request->host() != "www.esp8266fs.local";
}

void
HttpServerAsync::redirectToSelf(AsyncWebServerRequest *request) {
  AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
  response->addHeader("Location", String("http://") + "www.esp8266fs.local");
  request->send(response);
}

void
HttpServerAsync::start() {
  // Set up static content
  server->serveStatic("", SPIFFS, "");
  server->onNotFound([&](AsyncWebServerRequest *request){
    if (isIntercepted(request)) {
      redirectToSelf(request);
    } else {
      request->send(StatusCode::NotFound.getCode());
    }
  });
  server->begin();
}