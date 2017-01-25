#include "WiFiScanner.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace Messaging;

using namespace std::placeholders;

extern "C" {
  #include "user_interface.h"
}

bool WiFiScanner::isScanning = false;
std::list<WiFiScanner*> WiFiScanner::scanners;

namespace {

  std::string getEncryptionString(int encryption) {
    switch (encryption) {
      case AUTH_WEP:
        return "WEP";
      case AUTH_WPA_PSK:
        return "WPA";
      case AUTH_WPA2_PSK:
        return "WPA2";
      case AUTH_WPA_WPA2_PSK:
        return "AUTO";
      case AUTH_OPEN:
        return "NONE";
    }
    return "UNKNOWN";
  }

}

WiFiScanner::WiFiScanner(Messaging::IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue) {
  scanners.push_back(this);

  auto controller = messageQueue->createController("WiFiScanner");
  controller->addOnRequest("get", std::bind(&WiFiScanner::onGetNetworks, this));
}

WiFiScanner::~WiFiScanner() {
  scanners.remove(this);
}

IEntity::Unique
WiFiScanner::onGetNetworks() {
  if (!isScanning) {
    auto config = (const struct scan_config){ 0 };
    if (!wifi_station_scan(&config, reinterpret_cast<scan_done_cb_t>(&onScanDone))) {
      return Status::makeUnique(StatusCode::InternalServerError,
        "Unable to scan WiFi networks.");
    } else {
      isScanning = true;
    }
  }
  return Status::makeUnique(StatusCode::Accepted, "Scanning FiFi networks.");
}

void
WiFiScanner::onScanDone(void* result, int status) {
  IEntity::Unique eventContent;
  if (status == OK) {
    auto networks = Networks::makeUnique();
    bss_info* head = reinterpret_cast<bss_info*>(result);
    for(bss_info* it = head; it; it = STAILQ_NEXT(it, next)) {
      auto ssid = reinterpret_cast<const char*>(it->ssid);
      auto rssi = it->rssi;
      auto encryptionType = getEncryptionString(it->authmode);
      networks->add(Network(ssid, rssi, encryptionType));
    }
    eventContent = std::move(networks);
  } else {
    eventContent = Status::makeUnique(StatusCode::InternalServerError,
      "Failed to scan WiFi networks.");
  }
  isScanning = false;
  for(auto scanner: scanners) {
    scanner->controller->sendEvent("scanned", std::move(eventContent));
  }
}
