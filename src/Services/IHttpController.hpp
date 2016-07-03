// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_CONTROLLER_HPP
#define SERVICES_I_CONTROLLER_HPP

namespace Services {

class IHttpServer;

class IHttpController {
  public:
    virtual ~IHttpController();

    virtual void registerOn(IHttpServer& httpServer) = 0;
};

}

#endif /* end of include guard: SERVICES_I_CONTROLLER_HPP */
