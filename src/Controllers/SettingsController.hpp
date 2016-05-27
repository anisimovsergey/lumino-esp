// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_SETTINGS_CONTROLLER_H
#define CONTROLLERS_SETTINGS_CONTROLLER_H

#include "Services/IHttpServer.hpp"

namespace Controllers {

class SettingsController {
  public:
    // Register the controller on HTTP server.
    void registerOn(Services::IHttpServer& httpServer);

  private:
    void onGetSettings(Services::IHttpServer& httpServer);
    void onPutSettings(Services::IHttpServer& httpServer);
};

}

#endif /* end of include guard: CONTROLLERS_SETTINGS_CONTROLLER_H */
