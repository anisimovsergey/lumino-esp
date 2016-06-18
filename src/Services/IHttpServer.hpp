// Copyright Sergey Anisimov 2016-2017
// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTPSERVER_H
#define SERVICES_I_HTTPSERVER_H

#include "IHttpRequest.hpp"

#include "Core/ActionResult.hpp"
#include "Controllers/IApiController.hpp"

#include <functional>
#include <memory>

namespace Services {

class IHttpServer {
  public:
      typedef std::function<void(IHttpRequest& request)> TRequestHandler;
      typedef std::function<void(IHttpRequest& request,
        const Core::IEntity& entity)> TRequestWithEntityHandler;

      virtual std::shared_ptr<Core::ActionResult>
        addGetHandler(const String& uri,
        TRequestHandler fn) = 0;
      virtual std::shared_ptr<Core::ActionResult>
        addDeleteHandler(const String& uri,
        TRequestHandler fn) = 0;

      virtual std::shared_ptr<Core::ActionResult>
        addPostHandler(const String& uri,
        TRequestWithEntityHandler fn) = 0;
      virtual std::shared_ptr<Core::ActionResult>
        addPutHandler(const String& uri,
        TRequestWithEntityHandler fn) = 0;

      virtual void addApiController(
        std::shared_ptr<Controllers::IApiController> controller) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTPSERVER_H */
