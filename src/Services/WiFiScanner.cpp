#include "WiFiScanner.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace Messaging;

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
        return "WPA/PSK";
      case AUTH_WPA2_PSK:
        return "WPA2/PSK";
      case AUTH_WPA_WPA2_PSK:
        return "WPA/WPA2/PSK";
      case AUTH_OPEN:
        return "none";
    }
    return "unknown";
  }

}

WiFiScanner::WiFiScanner(Messaging::IMessageQueue& messageQueue) :
  messageQueue(messageQueue) {
  scanners.push_back(this);

  controller = messageQueue.createController(Networks::TypeId());
  controller->addOnRequest(RequestType("scan"), [=](){
    return onScanNetworks();
  });
}

WiFiScanner::~WiFiScanner() {
  scanners.remove(this);
}

std::unique_ptr<Core::IEntity>
WiFiScanner::onScanNetworks() {
  if (!isScanning) {
    auto config = (const struct scan_config){ 0 };
    if (!wifi_station_scan(&config, reinterpret_cast<scan_done_cb_t>(&onScanDone))) {
      return std::make_unique<Status>(StatusCode::InternalServerError,
        "Unable to scan WiFi networks.");
    } else {
      isScanning = true;
    }
  }
  return std::make_unique<Status>(StatusCode::Accepted, "Scanning WiFi networks.");
}

void
WiFiScanner::onScanDone(void* result, int status) {
  std::unique_ptr<IEntity> eventContent;
  if (status == OK) {
    auto networks = std::make_unique<Networks>();
    bss_info* head = reinterpret_cast<bss_info*>(result);
    for(bss_info* it = head; it; it = STAILQ_NEXT(it, next)) {
      auto ssid = reinterpret_cast<const char*>(it->ssid);
      auto rssi = it->rssi;
      auto encryptionType = getEncryptionString(it->authmode);
      networks->add(Network(ssid, rssi, encryptionType));
    }
    eventContent = std::move(networks);
  } else {
    eventContent = std::make_unique<Status>(StatusCode::InternalServerError,
      "Failed to scan WiFi networks.");
  }
  isScanning = false;
  for(auto scanner: scanners) {
    scanner->controller->sendEvent(EventType("scanned"), std::move(eventContent));
  }
}
