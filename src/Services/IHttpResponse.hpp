// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HTTP_RESPONSE_H
#define SERVICES_I_HTTP_RESPONSE_H

#include <WString.h>

namespace Services {

class IHttpResponse {
  public:
    virtual void setHeader(String header, String value) = 0;
    virtual void send() = 0;
};

}

#endif /* end of include guard: SERVICES_I_HTTP_RESPONSE_H */
