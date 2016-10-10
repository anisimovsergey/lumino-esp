#include "HttpServerAsync.hpp"

#include "Core/Memory.hpp"

#include <Hash.h>
#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpServerAsync::HttpServerAsync(
  int port,
  std::shared_ptr<const IWiFiManager> wifiManager) :
  server(Core::makeUnique<AsyncWebServer>(port)),
  wifiManager(wifiManager) {
}

HttpServerAsync::~HttpServerAsync() {
}

std::string
HttpServerAsync::getLocalDomain() {
  return wifiManager->getDeviceName() + ".local";
}

bool
HttpServerAsync::isIntercepted(AsyncWebServerRequest *request) {
  return request->host() != getLocalDomain().c_str();
}

void
HttpServerAsync::redirectToSelf(AsyncWebServerRequest *request) {
  auto route = std::string("http://") + getLocalDomain();
  request->redirect(route.c_str());
}

void
HttpServerAsync::start() {
  server->serveStatic("", SPIFFS, "");
  server->onNotFound([&](AsyncWebServerRequest *request){
    if (isIntercepted(request)) {
      redirectToSelf(request);
    } else {
      request->send((int)StatusCode::NotFound);
    }
  });
  server->begin();
}
