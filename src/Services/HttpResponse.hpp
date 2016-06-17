// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_RESPONSE_H
#define SERVICES_HTTP_RESPONSE_H

#include "IHttpResponse.hpp"

#include "Json/ISerializationService.hpp"

class AsyncWebServerResponse;

namespace Services {

class HttpResponse : public IHttpResponse {
  public:
    HttpResponse(
      AsyncWebServerResponse& response,
      const Json::ISerializationService& serializationService);
    virtual ~HttpResponse();

    void setLocation(const String& value) override;
    void sendJson(const Core::Status& status) override;
    void sendJson(const Core::IEntity& entity) override;

  private:
    AsyncWebServerResponse& response;
    const Json::ISerializationService& serializationService;
};

}

#endif /* end of include guard: SERVICES_HTTP_REQEST_H */
