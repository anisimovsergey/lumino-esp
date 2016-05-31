#include "NetworksController.hpp"

#include "Core/Status.hpp"
#include "Core/Logger.hpp"
#include "Services/IHttpServer.hpp"

using namespace Core;
using namespace Services;
using namespace Controllers;

NetworksController::NetworksController(
  std::shared_ptr<const IWiFiService> wifiService) :
  wifiService(wifiService) {
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
  Logger::message("Creating list");
  List<Models::Network> networks;
  Logger::message("Retrieving list of netorks...");
  Status status = wifiService->getWiFiNetworks(networks);
  Logger::message("List of netorks retrieved");
  if (status.isOk()) {
    Logger::message("Successfully");
    httpServer.sendJson(networks);
  } else {
    Logger::error(status.getTitle());
    httpServer.sendJson(status);
  }
}
