#include "HttpServerAsync.hpp"
#include "HttpRequest.hpp"

#include "Core/Utils.hpp"

#include <Hash.h>
#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpServerAsync::HttpServerAsync(
  int port,
  std::shared_ptr<const Json::ISerializationService> serializationService,
  std::shared_ptr<const IWiFiManager> wifiManager) :
  server(make_unique<AsyncWebServer>(port)),
  serializationService(serializationService),
  wifiManager(wifiManager) {
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
    if (statusResult->isOk()) {
      auto actionResult = requestHandler(httpRequest, *entity);
      sendResponse(httpRequest, *actionResult);
    } else {
      sendResponse(httpRequest, *statusResult);
    }
  }, nullptr, [&](AsyncWebServerRequest *request,
                  uint8_t *data, size_t len, size_t index, size_t total){
      if (index == 0) {
        request->_tempObject = malloc(total + 1);
        *((uint8_t*)request->_tempObject + total) = '\0';
      }
      if (request->_tempObject != nullptr) {
        memcpy((uint8_t*)request->_tempObject+index, data, len);
      }
    }
  );
}

void
HttpServerAsync::sendResponse(
  IHttpRequest& request,
  const IActionResult& actionResult) {

  auto sender = getSender(actionResult.getTypeId());
  if (!sender)
    return;

  std::unique_ptr<IHttpResponse> response;
  auto result = sender->getResponse(request, actionResult, response);
  if (!result->isOk())
    return;

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

String
HttpServerAsync::getLocalDomain() {
  return wifiManager->getDeviceName() + ".local";
}

bool
HttpServerAsync::isIntercepted(AsyncWebServerRequest *request) {
  return request->host() != getLocalDomain();
}

void
HttpServerAsync::redirectToSelf(AsyncWebServerRequest *request) {
  HttpRequest httpRequest(*request);
  auto route = String("http://") + getLocalDomain();
  auto redirectResult = RedirectResult::ToRoute(route);
  sendResponse(httpRequest, *redirectResult);
}

void
HttpServerAsync::start() {
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
