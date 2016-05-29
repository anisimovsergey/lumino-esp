// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTPSERVER_H
#define SERVICES_I_HTTPSERVER_H

#include "Core/Status.hpp"
#include "Core/IEntity.hpp"

#include <functional>

namespace Services {

class IHttpServer {
  public:
      typedef std::function<void(void)> THandlerFunction;

      virtual void addGetHandler(const String& uri,
                                 THandlerFunction fn) = 0;
      virtual void addPutHandler(const String& uri,
                                 THandlerFunction fn) = 0;

      virtual void sendJson(const Core::Status& status) = 0;
      virtual void sendJson(const Core::IEntity& value) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTPSERVER_H */
