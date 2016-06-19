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

HttpServerAsync::~HttpServerAsync() {
}

std::shared_ptr<Core::IActionResult>
HttpServerAsync::addGetHandler(const String& uri, TRequestHandler requestHandler) {
  addHandler(uri, HTTP_GET, requestHandler);
}

std::shared_ptr<Core::IActionResult>
HttpServerAsync::addDeleteHandler(const String& uri, TRequestHandler requestHandler) {
  addHandler(uri, HTTP_DELETE, requestHandler);
}

std::shared_ptr<Core::IActionResult>
HttpServerAsync::addPostHandler(
  const String& uri,
  TRequestWithEntityHandler requestHandler) {

}

std::shared_ptr<Core::IActionResult>
HttpServerAsync::addPutHandler(
  const String& uri,
  TRequestWithEntityHandler requestHandler) {

}

void
HttpServerAsync::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
}

void
HttpServerAsync::addHttpSender(std::shared_ptr<IHttpSender> httpSender) {
  senders.push_back(httpSender);
}

void
HttpServerAsync::addHandler(
  const String& uri,
  WebRequestMethod method,
  TRequestHandler requestHandler) {

  server->on(uri.c_str(), method, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request);
    sendResponse(httpRequest, requestHandler(httpRequest));
  });
}

void
HttpServerAsync::addHandler(
  const String& uri,
  WebRequestMethod method,
  TRequestWithEntityHandler requestHandler) {

  server->on(uri.c_str(), method, [=](AsyncWebServerRequest* request) {
    String body((char*)request->_tempObject);
    std::shared_ptr<IEntity> entity;
    HttpRequest httpRequest(*request);
    auto actionResult = serializationService->deserialize(body, entity);
    if (actionResult->isOk()) {
      actionResult = requestHandler(httpRequest, *entity);
    }
    sendResponse(httpRequest, actionResult);
  }, nullptr, [&](AsyncWebServerRequest *request,
    uint8_t *data, size_t len, size_t index, size_t total){
      if(index == 0)
        request->_tempObject = malloc(total);
      if(request->_tempObject != NULL)
        memcpy((uint8_t*)request->_tempObject+index, data, len);
    }
  );
}

void
HttpServerAsync::sendResponse(
  IHttpRequest& request,
  std::shared_ptr<Core::IActionResult> result) {

  String typeId = result->getTypeId();
  Logger::message("Getting sender for type " + typeId);
  auto sender = getSender(typeId);
  if (sender != nullptr) {
    sender->send(*serializationService, request, *result);
  }
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
