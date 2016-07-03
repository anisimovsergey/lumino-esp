// Copyright Sergey Anisimov 2016-2017
// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HPPTTPSERVER_HPP
#define SERVICES_I_HPPTTPSERVER_HPP

#include "IHttpRequest.hpp"
#include "IHttpSender.hpp"
#include "IHttpController.hpp"

#include "Core/ActionResult.hpp"

#include <functional>
#include <memory>

namespace Services {

class IHttpServer {
  public:
      typedef std::function<std::unique_ptr<Core::IActionResult>
        (IHttpRequest& request)> TRequestHandler;
      typedef std::function<std::unique_ptr<Core::IActionResult>
        (IHttpRequest& request,
         const Core::IEntity& entity)> TRequestWithEntityHandler;

      ~IHttpServer();

      virtual void addGetHandler(const String& uri,
        TRequestHandler requestHandler) = 0;
      virtual void addDeleteHandler(const String& uri,
        TRequestHandler requestHandler) = 0;
      virtual void addPostHandler(const String& uri,
        TRequestWithEntityHandler requestHandler) = 0;
      virtual void addPutHandler(const String& uri,
        TRequestWithEntityHandler frequestHandlern) = 0;

      virtual void addApiController(
        std::shared_ptr<IHttpController> controller) = 0;
      virtual void addHttpSender(
        std::shared_ptr<IHttpSender> httpSender) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HPPTTPSERVER_HPP */
