#include "NetworksController.hpp"

using namespace Core;
using namespace Services;
using namespace Controllers;

static const String WiFiNetworksUrl = "/wifi_networks";

NetworksController::NetworksController(
  std::shared_ptr<const IWiFiManager> wifiManager) :
  wifiManager(wifiManager) {
}

void
NetworksController::registerOn(IHttpServer& httpServer) {
  httpServer.addGetHandler(WiFiNetworksUrl, [&](IHttpRequest& request) {
    return onGetWiFiNetworks(request);
  });
}

std::unique_ptr<Core::IActionResult>
NetworksController::onGetWiFiNetworks(IHttpRequest& request) {

  auto message = request.createMessage(Message::GetWiFiNetworks);
  return messageQueue->addMessage(message);
}
