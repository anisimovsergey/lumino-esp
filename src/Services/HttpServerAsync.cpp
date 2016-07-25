#include "HttpServerAsync.hpp"

#include "Core/Utils.hpp"

#include <Hash.h>
#include <ESPAsyncWebServer.h>

using namespace Core;
using namespace Services;

HttpServerAsync::HttpServerAsync(
  int port,
  std::shared_ptr<const IWiFiManager> wifiManager) :
  server(make_unique<AsyncWebServer>(port)),
  wifiManager(wifiManager) {
}

HttpServerAsync::~HttpServerAsync() {
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
  //HttpRequest httpRequest(*request);
  //auto route = String("http://") + getLocalDomain();
  //auto redirectResult = RedirectResult::ToRoute(route);
  //sendResponse(httpRequest, *redirectResult);
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
