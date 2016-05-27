#include "NetworksController.hpp"

#include "Services/IHttpServer.hpp"

using namespace Services;
using namespace Controllers;

NetworksController::NetworksController(
  const Services::IWiFiService& wifiService) : wifiService(wifiService) {

}


void
NetworksController::onGetWiFiNetworks() {


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

void
NetworksController::registerOn(IHttpServer &server) {
  server.addGetHandler("/wifi_networks", [&]() { onGetWiFiNetworks(); });
}
