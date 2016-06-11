#include "NetworksController.hpp"

#include "Core/Status.hpp"
#include "Services/IHttpServer.hpp"

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
    this->onGetWiFiNetworks(request);
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
