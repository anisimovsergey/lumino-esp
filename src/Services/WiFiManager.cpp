#include "WiFiManager.hpp"
#include <ESP8266WiFi.h>

using namespace Services;

bool
WiFiManager::isConnected() {
  return (WiFi.status() == WL_CONNECTED);
}

void
WiFiManager::connect() {
  /*
  if (String(WiFi.SSID()) != network_ssid) {
    disconnectFromFiFi();
    WiFi.begin(network_ssid.c_str(), network_pswd.c_str());
    int i = 0;
    while ((WiFi.status() != WL_CONNECTED) && i < MAX_CONNECTION_WAIT) {
      delay(1000);
      i++;
    }
  }
  */
}

void
WiFiManager::disconnect() {
  /*
  if (WiFi.status() != WL_DISCONNECTED) {
    WiFi.disconnect();
    int i = 0;
    while ((WiFi.status() == WL_DISCONNECTED) && i < MAX_CONNECTION_WAIT) {
      delay(1000);
      i++;
    }
  }
  */
}
