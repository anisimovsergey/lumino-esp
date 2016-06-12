#include "NetworksController.hpp"

#include "Core/Status.hpp"
#include "Core/Logger.hpp"
#include "Services/IHttpServer.hpp"

#include <Arduino.h>

using namespace Core;
using namespace Services;
using namespace Controllers;

NetworksController::NetworksController(
  std::shared_ptr<const IWiFiManager> wifiManager) :
  wifiManager(wifiManager) {
}

void
NetworksController::registerOn(IHttpServer &httpServer) {
  httpServer.addGetHandler("/wifi_networks", [&](IHttpRequest& request) {
    Logger::message("/wifi_networks");
    onGetWiFiNetworks(request);
  });
}

void
NetworksController::onGetWiFiNetworks(IHttpRequest& request) {
  List<Models::Network> networks;
  Status status = wifiManager->getWiFiNetworks(networks);
  if (status.isOk()) {
    request.sendJson(networks);
  } else {
    request.sendJson(status);
  }
}
