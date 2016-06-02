#include "NetworksController.hpp"

#include "Core/Status.hpp"
#include "Core/Logger.hpp"
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
  httpServer.addGetHandler("/wifi_networks", [&]() {
    Logger::message("GET /wifi_networks");
    this->onGetWiFiNetworks(httpServer);
  });
}

void
NetworksController::onGetWiFiNetworks(IHttpServer& httpServer) {
  List<Models::Network> networks;
  Status status = wifiManager->getWiFiNetworks(networks);
  if (status.isOk()) {
    httpServer.sendJson(networks);
  } else {
    httpServer.sendJson(status);
  }
}
