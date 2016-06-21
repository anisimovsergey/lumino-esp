#include "NetworksController.hpp"

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
    return onGetWiFiNetworks(request);
  });
}

std::unique_ptr<Core::IActionResult>
NetworksController::onGetWiFiNetworks(IHttpRequest& request) {
  std::shared_ptr<List<Models::Network>> networks;
  auto actionResult = wifiManager->getWiFiNetworks(networks);
  if (!actionResult->isOk())
    return actionResult;

  return ObjectResult::OK(networks);
}
