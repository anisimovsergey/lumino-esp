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

void
HttpServerAsync::addGetHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_GET, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request, *serializationService);
    fn(httpRequest);
  });
}

void
HttpServerAsync::addPutHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_PUT, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request, *serializationService);
    fn(httpRequest);
  });
}

void
HttpServerAsync::addPostHandler(const String& uri, THandlerFunction fn) {
  String body;
  server->on(uri.c_str(), HTTP_POST, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request, body, *serializationService);
    fn(httpRequest);
  }, nullptr, [&](AsyncWebServerRequest *request,
    uint8_t *data, size_t len, size_t index, size_t total){
      String txt;
      Logger::message("Data len: " + String(len) +
        " index: " + String(index) +
        " total: " + String(total));
      txt.reserve(total);
      for (size_t i = index; i < index + len; i++) {
        char c = data[i];
        Logger::message("ch: " + String(c));
        txt += c;
      }
      Logger::message("Body: " + txt);
    }
  );
}

void
HttpServerAsync::addDeleteHandler(const String& uri, THandlerFunction fn) {
  server->on(uri.c_str(), HTTP_DELETE, [=](AsyncWebServerRequest* request) {
    HttpRequest httpRequest(*request, *serializationService);
    fn(httpRequest);
  });
}

void
HttpServerAsync::addApiController(std::shared_ptr<IApiController> controller) {
  controllers.push_back(controller);
  controller->registerOn(*this);
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
