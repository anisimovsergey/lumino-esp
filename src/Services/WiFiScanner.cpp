#include "WiFiScanner.hpp"

using namespace Core;
using namespace Services;

WiFiScanner::WiFiScanner(std::shared_ptr<Core::IMessageQueue> messageQueue) :
  messageQueue(messageQueue) {

  scanCompletedHandler = std::make_shared<std::function<void()>>(
    std::bind(&WiFiScanner::onScanCompleted, this));
  scanCompletedHandlers.push_back(scanCompletedHandler);
}

WiFiScanner::~WiFiScanner() {
  scanCompletedHandlers.remove(scanCompletedHandler);
}

void
WiFiScanner::notifyScanCompleted() {
  for (auto iterator = scanCompletedHandlers.begin(),
       end = scanCompletedHandlers.end();
       iterator != end; ++iterator) {
     (**iterator)();
  }
}

void
WiFiScanner::onGetWiFiNetworks() {

}

void
WiFiScanner::onScanCompleted() {
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
