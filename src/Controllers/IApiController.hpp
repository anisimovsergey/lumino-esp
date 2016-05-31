// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CONTROLLERS_I_API_CONTROLLER_H
#define CONTROLLERS_I_API_CONTROLLER_H

namespace Services {
  class IHttpServer;
}

namespace Controllers {

class IApiController {
  public:
    virtual void registerOn(Services::IHttpServer& httpServer) = 0;
};

}

#endif /* end of include guard: CONTROLLERS_I_API_CONTROLLER_H */
