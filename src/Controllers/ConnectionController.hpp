// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_CONNECTION_CONTROLLER_H
#define CONTROLLERS_CONNECTION_CONTROLLER_H

#include "IApiController.hpp"
#include "Services/IHttpServer.hpp"
#include "Services/IWiFiManager.hpp"

namespace Controllers {

class ConnectionController : public IApiController {
  public:
    ConnectionController(
      std::shared_ptr<Services::IWiFiManager> wifiManager);

    void registerOn(Services::IHttpServer& httpServer) override;

  private:
    std::shared_ptr<Services::IWiFiManager> wifiManager;

    void onGetConnection(Services::IHttpServer& httpServer);
    void onPostConnection(Services::IHttpServer& httpServer);
    void onDeleteConnection(Services::IHttpServer& httpServer);
};

}

#endif /* end of include guard: CONTROLLERS_CONNECTION_CONTROLLER_H */
