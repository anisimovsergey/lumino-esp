// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_CONNECTION_CONTROLLER_HPP
#define CONTROLLERS_CONNECTION_CONTROLLER_HPP

#include "Core/ActionResult.hpp"
#include "Services/IHttpController.hpp"
#include "Services/IHttpServer.hpp"
#include "Services/IWiFiManager.hpp"

#include <memory>

namespace Controllers {

class ConnectionController : public Services::IHttpController {
  public:
    ConnectionController(
      std::shared_ptr<Services::IWiFiManager> wifiManager);

    void registerOn(
      Services::IHttpServer& httpServer) override;

  private:
    std::shared_ptr<Services::IWiFiManager> wifiManager;

    std::unique_ptr<Core::IActionResult>
      onGetConnection(
        Services::IHttpRequest& request);

    std::unique_ptr<Core::IActionResult>
      onPostConnection(
        Services::IHttpRequest& request,
        const Core::IEntity& entity);

    std::unique_ptr<Core::IActionResult>
      onDeleteConnection(
        Services::IHttpRequest& request);
};

}

#endif /* end of include guard: CONTROLLERS_CONNECTION_CONTROLLER_HPP */
