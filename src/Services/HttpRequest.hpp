// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_HTTP_REQEST_H
#define SERVICES_HTTP_REQEST_H

#include "IHttpRequest.hpp"

#include "Json/ISerializationService.hpp"

class ESP8266WebServer;

namespace Services {

class HttpRequest : public IHttpRequest {
  public:
    HttpRequest(
      ESP8266WebServer& server,
      const Json::ISerializationService& serializationService);

    void addHeader(const String& header, const String& value) override;

    Core::Status getJson(
      std::shared_ptr<Core::IEntity>& entity) override;

    void sendJson(const Core::Status& status) override;
    void sendJson(const Core::IEntity& entity) override;

  private:
    const Json::ISerializationService& serializationService;
    ESP8266WebServer& server;
};

}

#endif /* end of include guard: SERVICES_HTTP_REQEST_H */
