// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFI_SCANNER_HPP
#define SERVICES_WIFI_SCANNER_HPP

#include "Messaging/IMessageQueue.hpp"
#include "Models/Networks.hpp"

#include <memory>
#include <list>

namespace Services {

class WiFiScanner {
  public:
    WiFiScanner(Messaging::IMessageQueue& messageQueue);
    ~WiFiScanner();

  private:
    Messaging::IMessageQueue&    messageQueue;
    std::unique_ptr<Messaging::QueueResourceController> controller;
    std::unique_ptr<Core::IEntity> onGetNetworks();

    static bool isScanning;
    static std::list<WiFiScanner*> scanners;
    static void onScanDone(void* result, int status);
};

}

#endif /* end of include guard: SERVICES_WIFI_SCANNER_HPP */
