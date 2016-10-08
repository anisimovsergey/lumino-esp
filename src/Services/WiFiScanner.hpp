// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFI_SCANNER_HPP
#define SERVICES_WIFI_SCANNER_HPP

#include "Core/IMessageQueue.hpp"
#include "Core/ILoopedService.hpp"
#include "Core/QueueResourceController.hpp"
#include "Models/Networks.hpp"

#include <memory>
#include <list>

namespace Services {

class WiFiScanner : public Core::ILoopedService  {
  TYPE_PTRS(WiFiScanner)
  public:
    WiFiScanner(Core::IMessageQueue::Shared messageQueue);
    ~WiFiScanner();

    void loop() {}

  private:
    Core::IMessageQueue::Shared    messageQueue;
    Core::QueueResourceController<Models::Networks>::Shared controller;
    Core::ActionResult::Unique onGetNetworks();

    static bool isScanning;
    static std::list<WiFiScanner*> scanners;
    static void onScanDone(void* result, int status);
};

}

#endif /* end of include guard: SERVICES_WIFI_SCANNER_HPP */
