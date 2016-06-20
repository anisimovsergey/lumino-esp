// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_NETWORKS_CONTROLLER_HPP
#define CONTROLLERS_NETWORKS_CONTROLLER_HPP

#include "IApiController.hpp"
#include "Core/ActionResult.hpp"
#include "Services/IHttpServer.hpp"
#include "Services/IWiFiManager.hpp"

#include "memory"

namespace Controllers {

class NetworksController : public IApiController {
  public:
    NetworksController(
      std::shared_ptr<const Services::IWiFiManager> wifiManager);

    void registerOn(Services::IHttpServer& httpServer) override;

  private:
    std::shared_ptr<const Services::IWiFiManager> wifiManager;

    std::shared_ptr<Core::IActionResult>
      onGetWiFiNetworks(Services::IHttpRequest& request);
};

}

#endif /* end of include guard: CONTROLLERS_NETWORKS_CONTROLLER_HPP */
