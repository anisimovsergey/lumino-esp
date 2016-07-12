// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFI_SCANNER_HPP
#define SERVICES_WIFI_SCANNER_HPP

#include "Core/IMessageQueue.hpp"

#include <memory>
#include <list>

namespace Services {

class WiFiScanner  {
  public:
    WiFiScanner(std::shared_ptr<Core::IMessageQueue> messageQueue);
    virtual ~WiFiScanner();

  private:
    static std::list<std::shared_ptr<std::function<void()>>> scanCompletedHandlers;
    static void notifyScanCompleted();

    std::shared_ptr<Core::IMessageQueue>    messageQueue;
    std::shared_ptr<std::function<void()>>  scanCompletedHandler;

    void    onGetWiFiNetworks();
    void    onScanCompleted();
};

}

#endif /* end of include guard: SERVICES_WIFI_SCANNER_HPP */
