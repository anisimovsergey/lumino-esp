// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_NETWORKS_CONTROLLER_HPP
#define CONTROLLERS_NETWORKS_CONTROLLER_HPP

#include "Services/IHttpController.hpp"
#include "Services/IHttpServer.hpp"
#include "Services/IWiFiManager.hpp"

#include "memory"

namespace Controllers {

class NetworksController : public Services::IHttpController {
  public:
    NetworksController(
      std::shared_ptr<const Services::IWiFiManager> wifiManager);

    void registerOn(
      Services::IHttpServer& httpServer) override;

  private:
    std::shared_ptr<const Services::IWiFiManager> wifiManager;

    std::unique_ptr<Core::IActionResult> onGetWiFiNetworks(
      Services::IHttpRequest& request);
};

}

#endif /* end of include guard: CONTROLLERS_NETWORKS_CONTROLLER_HPP */
