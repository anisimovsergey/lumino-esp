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

}
