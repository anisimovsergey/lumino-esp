#include "WiFiScanner.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

WiFiScanner::WiFiScanner(Core::IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue) {

  auto queueController = messageQueue->createController("WiFiScanner");
  controller = QueueResourceController<Networks>::makeUnique(queueController);

  controller->setOnGetRequestHandler(
    std::bind(&WiFiScanner::onGetNetworks, this));
}

WiFiScanner::~WiFiScanner() {
}

Core::ActionResult::Unique
WiFiScanner::onGetNetworks() {
  WiFi.scanNetworksAsync(
    std::bind(&WiFiScanner::onGetNetworks, this, _1)
  );
}

void
WiFiScanner::onScanCompleted(int) {
  /*
  void
  WiFiManager::onScanComplete() {

    Message message;
    auto networksCount = WiFi.scanComplete();
    if (networksCount >= 0) {
      auto networks = make_unique<List<Network>>();
      for (int networkNum = 0; networkNum < networksCount; networkNum++) {
        String ssid = WiFi.SSID(networkNum);
        int rssi = WiFi.RSSI(networkNum);
        int encryptionType = WiFi.encryptionType(networkNum);
        networks->add(Network(ssid, rssi, encryptionType));
      }
      WiFi.scanDelete();
      message = ObjectResult::OK(std::move(networks));
    } else {
      message = StatusResult::InternalServerError("Unable to scan WiFi networks.");
    }
    messageQueue->addMessage(message);
  }
  */
}
