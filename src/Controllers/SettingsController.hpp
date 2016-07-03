// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_SETTINGS_CONTROLLER_HPP
#define CONTROLLERS_SETTINGS_CONTROLLER_HPP

#include "Services/IHttpController.hpp"
#include "Services/IHttpServer.hpp"
#include "Services/IWiFiManager.hpp"

namespace Controllers {

class SettingsController : public Services::IHttpController {
  public:
    SettingsController(
      std::shared_ptr<const Services::IWiFiManager> wifiManager);

    void registerOn(
      Services::IHttpServer& httpServer) override;

  private:
    std::shared_ptr<const Services::IWiFiManager> wifiManager;

    std::unique_ptr<Core::IActionResult> onGetSettings(
        Services::IHttpRequest& request);

    std::unique_ptr<Core::IActionResult> onPutSettings(
        Services::IHttpRequest& request,
        const Core::IEntity& entity);
};

}

#endif /* end of include guard: CONTROLLERS_SETTINGS_CONTROLLER_HPP */
