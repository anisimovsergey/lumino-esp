// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFI_SCANNER_HPP
#define SERVICES_WIFI_SCANNER_HPP

#include "Core/IService.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "Messaging/QueueResourceController.hpp"
#include "Models/Networks.hpp"

#include <memory>
#include <list>

namespace Services {

class WiFiScanner : public Core::IService  {
  TYPE_PTRS(WiFiScanner)
  public:
    WiFiScanner(Messaging::IMessageQueue::Shared messageQueue);
    ~WiFiScanner();

    void idle() {}

  private:
    Messaging::IMessageQueue::Shared    messageQueue;
    Messaging::QueueResourceController::Shared controller;
    Core::IEntity::Unique onGetNetworks();

    static bool isScanning;
    static std::list<WiFiScanner*> scanners;
    static void onScanDone(void* result, int status);
};

}

#endif /* end of include guard: SERVICES_WIFI_SCANNER_HPP */
