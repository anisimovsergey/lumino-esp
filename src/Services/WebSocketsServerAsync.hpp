// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WEBSOCKETS_SERVER_HPP
#define SERVICES_WEBSOCKETS_SERVER_HPP

#include "Core/ILoopedService.hpp"
#include "Json/ISerializationService.hpp"

#include <WebSocketsServer.h>

#include <memory>

namespace Services {

class WebSocketsServerAsync : public Core::ILoopedService {
  public:
    WebSocketsServerAsync(int port,
      std::shared_ptr<const Json::ISerializationService> serializer);
    ~WebSocketsServerAsync();

    void start() {};
    void loop() override { server->loop(); };

  private:
    std::unique_ptr<WebSocketsServer> server;
    std::shared_ptr<const Json::ISerializationService> serializer;

    void onSocketEvent(uint8_t num, WStype_t type, uint8_t * payload,
      size_t length);
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
