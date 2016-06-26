#include "HttpServerAsync.hpp"

#include "HttpRequest.hpp"

#include "Core/Logger.hpp"
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
HttpServerAsync::addGetHandler(const String& uri, TRequestHandler requestHandler) {
  addHandler(uri, HTTP_GET, requestHandler);
}

void
HttpServerAsync::addDeleteHandler(const String& uri, TRequestHandler requestHandler) {
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
HttpServerAsync::addApiController(std::shared_ptr<IHttpController> controller) {
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
  int method,
  TRequestHandler requestHandler) {

  server->on(uri.c_str(), (WebRequestMethod)method, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request);
    auto actionResult = requestHandler(httpRequest);
    Logger::message("Action result type " + actionResult->getTypeId());
    sendResponse(httpRequest, *actionResult);
  });
}

void
HttpServerAsync::addHandler(
  const String& uri,
  int method,
  TRequestWithEntityHandler requestHandler) {

  server->on(uri.c_str(), (WebRequestMethod)method, [=](AsyncWebServerRequest* request) {
    Logger::message("Creating body");
    String body((char*)request->_tempObject);
    Logger::message("Created: " + body);
    HttpRequest httpRequest(*request);
    std::shared_ptr<IEntity> entity;
    auto actionResult = serializationService->deserialize(body, entity);
    if (actionResult->isOk()) {
      actionResult = requestHandler(httpRequest, *entity);
    }
    sendResponse(httpRequest, *actionResult);
  }, nullptr, [&](AsyncWebServerRequest *request,
    uint8_t *data, size_t len, size_t index, size_t total){
      if (index == 0) {
        Logger::message("Allocating " + String(total));
        request->_tempObject = malloc(total + 1);
        *((uint8_t*)request->_tempObject + total) = '\0';
        Logger::message("Allocated");
      }
      if(request->_tempObject != NULL) {
        Logger::message("Copying to index:" + String(index) + " len:" + String(len));
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
  Logger::message("Getting sender for type " + typeId);
  auto sender = getSender(typeId);
  if (sender) {
    Logger::message("Sender found sending...");
    sender->send(request, result);
    Logger::message("Sent");
  } else {
    auto response = request.createResponse(StatusCode::InternalServerError.getCode());
    response->send();
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
  //Logger::message("Request redirected");
  AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
  response->addHeader("Location", String("http://") + "www.esp8266fs.local");
  request->send(response);
}

void
HttpServerAsync::start() {
  // Set up static content
  server->serveStatic("", SPIFFS, "");
  server->onNotFound([&](AsyncWebServerRequest *request){
    //Logger::message("Request Header:" + request->host() + " Uri:" + request->url());
    if (isIntercepted(request)) {
      redirectToSelf(request);
    } else {
      request->send(404);
    }
  });
  server->begin();
  Logger::message("HTTP asynchronous server started");
}
