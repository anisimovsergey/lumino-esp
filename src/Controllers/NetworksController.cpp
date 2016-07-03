#include "NetworksController.hpp"

using namespace Core;
using namespace Services;
using namespace Controllers;

NetworksController::NetworksController(
  std::shared_ptr<const IWiFiManager> wifiManager) :
  wifiManager(wifiManager) {
}

void
NetworksController::registerOn(IHttpServer& httpServer) {
  httpServer.addGetHandler("/wifi_networks", [&](IHttpRequest& request) {
    return onGetWiFiNetworks(request);
  });
}

std::unique_ptr<Core::IActionResult>
NetworksController::onGetWiFiNetworks(IHttpRequest& request) {
  std::unique_ptr<Core::List<Models::Network>> networks;
  auto result = wifiManager->getWiFiNetworks(networks);
  if (!result->isOk())
    return StatusResult::InternalServerError("Unable to scan WiFi networks",
      std::move(result));
  return ObjectResult::OK(std::move(networks));
}
