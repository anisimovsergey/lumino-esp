// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_NETWORKS_CONTROLLER_H
#define CONTROLLERS_NETWORKS_CONTROLLER_H

#include "IApiController.hpp"
#include "Services/IHttpServer.hpp"
#include "Services/IWiFiService.hpp"

namespace Controllers {

class NetworksController : public IApiController {
  public:
    NetworksController(const Services::IWiFiService& wifiService);

    void registerOn(Services::IHttpServer& httpServer) override;

  private:
    const Services::IWiFiService& wifiService;

    void onGetWiFiNetworks(Services::IHttpServer& httpServer);
};

}

#endif /* end of include guard: CONTROLLERS_NETWORKS_CONTROLLER_H */
