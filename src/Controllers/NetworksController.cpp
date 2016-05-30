#include "NetworksController.hpp"

#include "Core/Status.hpp"
#include "Core/Logger.hpp"
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
    Logger::message("GET /wifi_networks");
    onGetWiFiNetworks(httpServer);
  });
}

void
NetworksController::onGetWiFiNetworks(Services::IHttpServer& httpServer) {
  List<Models::Network> networks;
  const Status& status = wifiService.getWiFiNetworks(networks);
  if (status.isOk()) {
    Logger::message("List of networks retrieved");
    httpServer.sendJson(networks);
  } else {
    Logger::error(status.getTitle());
    httpServer.sendJson(status);
  }
}
