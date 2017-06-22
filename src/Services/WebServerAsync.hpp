// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef SERVICES_WEB_SERVER_ASYNC_HPP
#define SERVICES_WEB_SERVER_ASYNC_HPP

#include "Core/ILogger.hpp"
#include "Models/AccessPoint.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "Serialization/ISerializationService.hpp"

#include <WString.h>
#include <Hash.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWebServer.h>

#include <memory>
#include <list>

namespace Services {

class WebServerAsync {
  public:
    WebServerAsync(
      Messaging::IMessageQueue& messageQueue,
      Serialization::ISerializationService& serializer,
      Core::ILogger& logger);

    void start();

  private:
    typedef std::list<std::unique_ptr<Messaging::QueueGenericClient>> QueueClients;
    typedef std::unique_ptr<Messaging::QueueResourceClient> AccessPointClient;

    std::unique_ptr<AsyncWebServer>       httpServer;
    std::unique_ptr<AsyncWebSocket>       wsServer;
    Messaging::IMessageQueue&             messageQueue;
    Serialization::ISerializationService& serializer;
    Core::ILogger&                        logger;
    QueueClients                          queueClients;
    AccessPointClient                     accessPointClient;

    void onAccessPointCreated(const Models::AccessPoint& accessPoint);

    std::string     getLocalDomain() const;

    bool    isIntercepted(AsyncWebServerRequest* request);
    void    redirectToSelf(AsyncWebServerRequest* request);

    void onSocketEvent(AsyncWebSocketClient* client,
      AwsEventType type, void* arg, uint8_t *data, size_t len);

    std::string getClientId(AsyncWebSocketClient* client);
    Messaging::QueueGenericClient* findQueueClient(AsyncWebSocketClient* client);
    void sendToClinet(AsyncWebSocketClient* client, const Core::IEntity& entity);

    // Events
    void onClientConnected(AsyncWebSocketClient* client);
    void onClientDisconnected(AsyncWebSocketClient* client);
    void onTextReceived(AsyncWebSocketClient* client, const std::string& text);
    void onResponse(AsyncWebSocketClient* client, const Messaging::Response& response);
    void onNotification(AsyncWebSocketClient* client, const Messaging::Event& event);
};

}

#endif /* end of include guard: SERVICES_WEB_SERVER_ASYNC_HPP */
