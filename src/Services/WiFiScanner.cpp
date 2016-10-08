#include "WiFiScanner.hpp"

#include "Core/ObjectResult.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

extern "C" {
  #include "user_interface.h"
}

bool WiFiScanner::isScanning = false;
std::list<WiFiScanner*> WiFiScanner::scanners;

WiFiScanner::WiFiScanner(IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue) {
  scanners.push_back(this);

  auto queueController = messageQueue->createController("WiFiScanner");
  controller = QueueResourceController<Networks>::makeUnique(queueController);

  controller->setOnGetRequestHandler(
    std::bind(&WiFiScanner::onGetNetworks, this));
}

WiFiScanner::~WiFiScanner() {
  scanners.remove(this);
}

ActionResult::Unique
WiFiScanner::onGetNetworks() {
  if (!isScanning) {
    auto config = (const struct scan_config){ 0 };
    if (!wifi_station_scan(&config, reinterpret_cast<scan_done_cb_t>(&onScanDone))) {
      return StatusResult::makeUnique(StatusCode::InternalServerError,
        "Unable to scan WiFi networks.");
    }
  }
  return StatusResult::makeUnique(StatusCode::Accepted, "Scanning FiFi networks.");
}

void
WiFiScanner::onScanDone(void* result, int status) {
  ActionResult::Unique actionResult;
  if (status == OK) {
    auto networks = Networks::makeUnique();
    bss_info* head = reinterpret_cast<bss_info*>(result);
    for(bss_info* it = head; it; it = STAILQ_NEXT(it, next)) {
      auto ssid = reinterpret_cast<const char*>(it->ssid);
      int rssi = it->rssi;
      int encryptionType = it->authmode;
      networks->add(Network(ssid, rssi, encryptionType));
    }
    actionResult = ObjectResult::makeUnique(StatusCode::OK, std::move(networks));
  } else {
    actionResult = StatusResult::makeUnique(StatusCode::InternalServerError,
      "Failed to scan WiFi networks.");
  }
  isScanning = false;
  for(auto scanner: scanners) {
    scanner->controller->sendGetNotification(std::move(actionResult));
  }
}
