// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WEB_SERVER_ASYNC_HPP
#define SERVICES_WEB_SERVER_ASYNC_HPP

#include "Settings.hpp"
#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Json/ISerializationService.hpp"

#include <memory>
#include <list>
#include <algorithm>

#include <Hash.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWebServer.h>

namespace Services {

class WebServerAsync : public Core::ILoopedService {
  TYPE_PTRS(WebServerAsync)
  public:
    WebServerAsync(
      std::shared_ptr<const Settings> settings,
      Core::IMessageQueue::Shared messageQueue,
      Json::ISerializationService::Shared serializer);
    virtual ~WebServerAsync();

    void start();
    void loop() override { };

  private:
    std::shared_ptr<const Settings>       settings;
    std::unique_ptr<AsyncWebServer>       httpServer;
    std::unique_ptr<AsyncWebSocket>       wsServer;
    Core::IMessageQueue::Shared           messageQueue;
    Json::ISerializationService::Shared   serializer;
    std::list<Core::QueueClient::Shared>  queueClients;

    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);

    void onSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
      AwsEventType type, void* arg, uint8_t *data, size_t len);

    std::string getClientId(AsyncWebSocketClient* client);
    Core::QueueClient::Shared findQueueClient(AsyncWebSocketClient* client);
    void sendToClinet(AsyncWebSocketClient* client, const Core::IEntity& entity);

    // Events
    void onClientConnected(AsyncWebSocketClient* client);
    void onClientDisconnected(AsyncWebSocketClient* client);
    void onTextReceived(AsyncWebSocketClient* client, const std::string& text);
    void onResponse(AsyncWebSocketClient* client, const Core::Response& response);
    void onNotification(AsyncWebSocketClient* client, const Core::Notification& notification);
};

}

#endif /* end of include guard: SERVICES_WEB_SERVER_ASYNC_HPP */
