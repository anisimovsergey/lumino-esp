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
#include <list>

namespace Services {

class WebSocketsServerAsync : public Core::ILoopedService {
  TYPE_PTRS(WebSocketsServerAsync)
  public:
    WebSocketsServerAsync(
      Core::IMessageQueue::Shared messageQueue,
      Json::ISerializationService::Shared serializer);
    ~WebSocketsServerAsync();

    void start() {};
    void loop() override { };

    std::unique_ptr<AsyncWebSocket> server;
  private:
    Core::IMessageQueue::Shared messageQueue;
    Json::ISerializationService::Shared serializer;
    std::list<Core::QueueClient::Shared> queueClients;

    void onSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
      AwsEventType type, void* arg, uint8_t *data, size_t len);

    String getClientId(AsyncWebSocketClient* client);
    Core::QueueClient::Shared findQueueClient(AsyncWebSocketClient* client);
    void sendToClinet(AsyncWebSocketClient* client, const Core::IEntity& entity);

    // Events
    void onClientConnected(AsyncWebSocketClient* client);
    void onClientDisconnected(AsyncWebSocketClient* client);
    void onTextReceived(AsyncWebSocketClient* client, const String& text);
    void onResponse(AsyncWebSocketClient* client, const Core::Response& response);
    void onNotification(AsyncWebSocketClient* client, const Core::Notification& notification);
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
