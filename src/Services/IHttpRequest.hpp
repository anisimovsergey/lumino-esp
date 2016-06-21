// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_HPPTTP_REQEST_HPP
#define SERVICES_I_HPPTTP_REQEST_HPP

#include "IHttpResponse.hpp"
#include "Core/IEntity.hpp"

#include <WString.h>

#include <memory>

namespace Services {

class IHttpRequest {
  public:
    virtual String getArgument(String parameter) = 0;

    virtual String getHeader(String header) = 0;

    virtual std::unique_ptr<IHttpResponse> createResponse(
      int code) = 0;
      
    virtual std::unique_ptr<IHttpResponse> createResponse(
      int code, String contentType, String content) = 0;
};

}

#endif /* end of include guard: SERVICES_I_HPPTTP_REQEST_HPP */
