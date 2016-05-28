#include "NetworksController.hpp"

#include "Core/Status.hpp"
#include "Services/IHttpServer.hpp"

using namespace Core;
using namespace Services;
using namespace Controllers;

NetworksController::NetworksController(
  const Services::IWiFiService& wifiService) : wifiService(wifiService) {
}

void
NetworksController::registerOn(IHttpServer &httpServer) {
  httpServer.addGetHandler("/wifi_networks", [&]() {
    onGetWiFiNetworks(httpServer);
  });
}

void
NetworksController::onGetWiFiNetworks(Services::IHttpServer& httpServer) {
  List<Models::Network> networks;
  const Status& status = wifiService.getWiFiNetworks(networks);
  if (status.isOk()) {
    httpServer.sendJson(networks);
  } else {
    httpServer.sendJson(status);
  }
}
