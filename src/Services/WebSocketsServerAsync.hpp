// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WEBSOCKETS_SERVER_HPP
#define SERVICES_WEBSOCKETS_SERVER_HPP

#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Json/ISerializationService.hpp"

#include "ESPAsyncWebServer.h"

#include <memory>

namespace Services {

class WebSocketsServerAsync : public Core::ILoopedService {
  public:
    WebSocketsServerAsync(int port,
      std::shared_ptr<Core::IMessageQueue> messageQueue,
      std::shared_ptr<const Json::ISerializationService> serializer);
    ~WebSocketsServerAsync();

    void start() {};
    void loop() override { };

  
    std::unique_ptr<AsyncWebSocket> server;
  private:
    std::shared_ptr<Core::IMessageQueue> messageQueue;
    std::shared_ptr<const Json::ISerializationService> serializer;

    void onSocketEvent(AsyncWebSocket * server, AsyncWebSocketClient * client,
      AwsEventType type, void * arg, uint8_t *data, size_t len);

    void sendResponse(uint32_t num,
      std::unique_ptr<Core::StatusResult>&& result,
      const Core::Request* request);

    void onResponse(std::shared_ptr<Core::Response> response);
    void onNotification(std::shared_ptr<Core::Notification> notification);
    void onBroadcast(std::shared_ptr<Core::Notification> notification);
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
