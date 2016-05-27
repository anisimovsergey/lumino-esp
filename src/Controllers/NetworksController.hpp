// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_NETWORKS_CONTROLLER_H
#define CONTROLLERS_NETWORKS_CONTROLLER_H

#include "Services/IHttpServer.hpp"
#include "Services/IWiFiService.hpp"

namespace Controllers {

class NetworksController {
  public:
    NetworksController(const Services::IWiFiService& wifiService);

    // Register the controller on HTTP server.
    void registerOn(Services::IHttpServer& server);

  private:
    const Services::IWiFiService& wifiService;

    void onGetWiFiNetworks();
};

}

#endif /* end of include guard: CONTROLLERS_NETWORKS_CONTROLLER_H */
