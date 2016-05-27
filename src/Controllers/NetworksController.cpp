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
  std::list<Models::Network> networks;
  const Status& status = wifiService.getWiFiNetworks(networks);
  if (status.isOk()) {
    httpServer.sendJson(&status);
  } else {
    httpServer.sendJson(&networks);
  }
  /*
  void onGetWiFiNetworks() {
    int networksCount = WiFi.scanNetworks();
    if (networksCount == -1) {
      server.sendError(Errors.UnableToScanFiFiNetworks);
    } else {
      String json = "[";
      for (int networkNum = 0; networkNum < networksCount; networkNum++) {
        json += "{";
        json += "\"ssid\": \"" + WiFi.SSID(networkNum) + "\",";
        json += "\"rssi\": " + String(WiFi.RSSI(networkNum)) + ",";
        json += "\"encryption\": \"" + getEncryptionType(WiFi.encryptionType(networkNum)) + "\"";
        json += "}";
        if (networkNum < networksCount - 1)
          json += ",";
      }
      json += "]";
      server.send(200, "text/json", json);
    }
  }
  */
}
