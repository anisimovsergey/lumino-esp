// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTPSERVER_H
#define SERVICES_I_HTTPSERVER_H

#include <functional>

namespace Services {

class IHttpServer {
  public:
      typedef std::function<void(void)> THandlerFunction;

      virtual void addGetHandler(const char* uri,
                                 THandlerFunction fn) = 0;
      virtual void addPutHandler(const char* uri,
                                 THandlerFunction fn) = 0;
};
  
}

#endif /* end of include guard: SERVICES_I_HTTPSERVER_H */
