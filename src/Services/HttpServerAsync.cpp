#include "HttpServerAsync.hpp"

#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

#include <FS.h>
#include <WString.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpServerAsync::HttpServerAsync(
  int port) :
  server(new AsyncWebServer(port)) {
}

HttpServerAsync::~HttpServerAsync() {

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
