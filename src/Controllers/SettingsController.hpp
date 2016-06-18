// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_SETTINGS_CONTROLLER_H
#define CONTROLLERS_SETTINGS_CONTROLLER_H

#include "IApiController.hpp"
#include "Services/IHttpServer.hpp"
#include "Services/IWiFiManager.hpp"

namespace Controllers {

class SettingsController : public IApiController {
  public:
    SettingsController(
      std::shared_ptr<const Services::IWiFiManager> wifiManager);

    void registerOn(Services::IHttpServer& httpServer) override;

  private:
    std::shared_ptr<const Services::IWiFiManager> wifiManager;

    std::shared_ptr<Core::ActionResult>
      onGetSettings(
        Services::IHttpRequest& request);
        
    std::shared_ptr<Core::ActionResult>
      onPutSettings(
        Services::IHttpRequest& request,
        const Core::IEntity& entity);
};

}

#endif /* end of include guard: CONTROLLERS_SETTINGS_CONTROLLER_H */
