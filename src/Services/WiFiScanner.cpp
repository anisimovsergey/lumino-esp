#include "WiFiScanner.hpp"

#include "Core/ObjectResult.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

WiFiScanner::WiFiScanner(IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue) {

  auto queueController = messageQueue->createController("WiFiScanner");
  controller = QueueResourceController<Networks>::makeUnique(queueController);

  controller->setOnGetRequestHandler(
    std::bind(&WiFiScanner::onGetNetworks, this));
}

ActionResult::Unique
WiFiScanner::onGetNetworks() {
  auto networksCount = WiFi.scanNetworks();
  if (networksCount < 0) {
    return StatusResult::makeUnique(StatusCode::InternalServerError,
      "Unable to scan WiFi networks.");
  }
  auto networks = Networks::makeUnique();
  for (int networkNum = 0; networkNum < networksCount; networkNum++) {
    auto ssid = WiFi.SSID(networkNum);
    int rssi = WiFi.RSSI(networkNum);
    int encryptionType = WiFi.encryptionType(networkNum);
    networks->add(Network(ssid.c_str(), rssi, encryptionType));
  }
  WiFi.scanDelete();
  return ObjectResult::makeUnique(StatusCode::OK, std::move(networks));
}
