// Copyright Sergey Anisimov 2016-2017
// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTPSERVER_H
#define SERVICES_I_HTTPSERVER_H

#include "IHttpRequest.hpp"

#include "Controllers/IApiController.hpp"

#include <functional>
#include <memory>

namespace Services {

class IHttpServer {
  public:
      typedef std::function<void(IHttpRequest& request)> THandlerFunction;

      virtual void addGetHandler(const String& uri,
                                 THandlerFunction fn) = 0;
      virtual void addPutHandler(const String& uri,
                                 THandlerFunction fn) = 0;
      virtual void addPostHandler(const String& uri,
                                  THandlerFunction fn) = 0;
      virtual void addDeleteHandler(const String& uri,
                                    THandlerFunction fn) = 0;

      virtual void addApiController(
        std::shared_ptr<Controllers::IApiController> controller) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTPSERVER_H */
