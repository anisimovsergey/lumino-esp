#include "WebSocketsServerAsync.hpp"

#include <Core/Memory.hpp>
#include <Core/Logger.hpp>
#include <Core/IMessage.hpp>

using namespace Core;
using namespace Services;
using namespace std::placeholders;

WebSocketsServerAsync::WebSocketsServerAsync(int port,
  std::shared_ptr<IMessageQueue> messageQueue,
  std::shared_ptr<Json::ISerializationService> serializer) :
  server(make_unique<AsyncWebSocket>("/ws")), messageQueue(messageQueue),
  serializer(serializer) {

  server->onEvent(std::bind(&WebSocketsServerAsync::onSocketEvent, this,
    _1, _2, _3, _4, _5, _6));
}

WebSocketsServerAsync::~WebSocketsServerAsync() {

}

void
WebSocketsServerAsync::sendResult(AsyncWebSocketClient* client,
  const Core::StatusResult& result) {
  String json;
  auto status = serializer->serialize(result, json);
  if (status->isOk()) {
    client->text(json);
  } else {
    Logger::error("Unbale to seraile the response.");
  }
}

void
WebSocketsServerAsync::onSocketEvent(AsyncWebSocket* server,
  AsyncWebSocketClient* client, AwsEventType type, void * arg,
  uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      onClientConnected(client);
    case WS_EVT_DISCONNECT:
      onClientDisconnected(client);
    case WS_EVT_DATA: {
      AwsFrameInfo * info = (AwsFrameInfo*)arg;
      if (!(info->final && info->index == 0 && info->len == len) ||
          info->opcode != WS_TEXT)
        return;
      data[len] = 0;
      onTextReceived(client, (char*)data);
    }
    default:
      break;
  }
}

String
WebSocketsServerAsync::getClientId(AsyncWebSocketClient* client) {
  return "WebSocketsServer/" + String(client->id());
}

Core::QueueClient::Shared
WebSocketsServerAsync::findQueueClient(AsyncWebSocketClient* client) {
  auto clientId = getClientId(client);
  for(auto client: queueClients) {
    if (client->getId() == clientId)
      return client;
  }
  return nullptr;
}

void
WebSocketsServerAsync::onClientConnected(AsyncWebSocketClient* client) {
  auto clientId = getClientId(client);
  auto queueClinet = messageQueue->createClient(clientId);
  queueClinet->setOnResponse([=](const Response& response){
    onResponse(client, response);
  });
  queueClinet->setOnNotification([=](const Notification& notification){
    onNotification(client, notification);
  });
  queueClients.push_back(queueClinet);
}

void
WebSocketsServerAsync::onClientDisconnected(AsyncWebSocketClient* client) {
  auto queueClient = findQueueClient(client);
  if (queueClient) {
    messageQueue->removeClient(queueClient);
    queueClients.remove(queueClient);
  }
}

void
WebSocketsServerAsync::onTextReceived(AsyncWebSocketClient* client, const String& text) {
  std::unique_ptr<IEntity> entity;
  std::shared_ptr<Request> request;
  auto statusResult = serializer->deserialize(text, entity);
  if (statusResult->isOk()) {
    request = castToShared<Request>(std::move(entity));
    if (request) {
      auto queueClient = findQueueClient(client);
      if (queueClient)
        statusResult = queueClient->sendMessage(request);
      else
        statusResult = StatusResult::InternalServerError(
          "Unable to find queue client '" + String(client->id()) +"'.");
    } else {
      statusResult = StatusResult::BadRequest(
        "Type '" + String(Request::TypeId) + "' was expected.");
    }
  }
  if (!statusResult->isOk()) {
    sendResult(client, *statusResult);
  }
}

void
WebSocketsServerAsync::onResponse(AsyncWebSocketClient* client, const Response& response) {
  String json;
  auto status = serializer->serialize(response, json);
  if (status->isOk()) {
    client->text(json);
  } else {
    Logger::error("Unbale to seraile the response.");
  }
}

void
WebSocketsServerAsync::onNotification(AsyncWebSocketClient* client, const Notification& notification) {
  String json;
  auto status = serializer->serialize(notification, json);
  if (status->isOk()) {
    client->text(json);
  } else {
    Logger::error("Unbale to seraile the notification.");
  }
}
