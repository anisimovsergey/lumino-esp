// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_REQEST_H
#define SERVICES_HTTP_REQEST_H

#include "IHttpRequest.hpp"

#include "Json/ISerializationService.hpp"

class AsyncWebServerRequest;

namespace Services {

class HttpRequest : public IHttpRequest {
  public:
    HttpRequest(
      AsyncWebServerRequest& request,
      const String& body,
      const Json::ISerializationService& serializationService);
    virtual ~HttpRequest();

    Core::Status getJson(
      std::shared_ptr<Core::IEntity>& entity) override;

    std::shared_ptr<IHttpResponse> createResponse(
      const Core::Status& status) override;

  private:
    AsyncWebServerRequest& request;
    const String& body;
    const Json::ISerializationService& serializationService;
};

}

#endif /* end of include guard: SERVICES_HTTP_REQEST_H */
