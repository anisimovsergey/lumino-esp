#include "WebSocketsServerAsync.hpp"

#include <Core/Memory.hpp>
#include <Core/Casting.hpp>
#include <Core/Logger.hpp>
#include <Core/Message.hpp>
#include <Core/StringFormat.hpp>

using namespace Core;
using namespace Services;
using namespace std::placeholders;

WebSocketsServerAsync::WebSocketsServerAsync(
  IMessageQueue::Shared messageQueue,
  Json::ISerializationService::Shared serializer) :
  server(Core::makeUnique<AsyncWebSocket>("/ws")), messageQueue(messageQueue),
  serializer(serializer) {

  server->onEvent(std::bind(&WebSocketsServerAsync::onSocketEvent, this,
    _1, _2, _3, _4, _5, _6));
}

WebSocketsServerAsync::~WebSocketsServerAsync() {
}

void
WebSocketsServerAsync::sendToClinet(AsyncWebSocketClient* client,
  const Core::IEntity& entity) {
  std::string json;
  auto status = serializer->serialize(entity, json);
  if (status->isOk()) {
    client->text(json.c_str());
  } else {
    status = serializer->serialize(*status, json);
    if (status->isOk())
      client->text(json.c_str());
    else
      Logger::error("Unable to seraile the response of type '" +
        std::string(status->getTypeId()) + "'.");
  }
}

void
WebSocketsServerAsync::onSocketEvent(AsyncWebSocket* server,
  AsyncWebSocketClient* client, AwsEventType type, void * arg,
  uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      onClientConnected(client);
      break;
    case WS_EVT_DISCONNECT:
      onClientDisconnected(client);
      break;
    case WS_EVT_DATA: {
      AwsFrameInfo * info = (AwsFrameInfo*)arg;
      if (!(info->final && info->index == 0 && info->len == len) ||
          info->opcode != WS_TEXT)
        return;
      data[len] = 0;
      onTextReceived(client, (char*)data);
      break;
    }
    default:
      break;
  }
}

std::string
WebSocketsServerAsync::getClientId(AsyncWebSocketClient* client) {
  return "WebSocketsServer/" + toString(client->id());
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
  Logger::message("Client '" + clientId + "' connected.");
}

void
WebSocketsServerAsync::onClientDisconnected(AsyncWebSocketClient* client) {
  auto queueClient = findQueueClient(client);
  if (queueClient) {
    messageQueue->removeClient(queueClient);
    queueClients.remove(queueClient);
    Logger::message("Client '" + queueClient->getId() + "' disconnected.");
  } else {
    Logger::error("Client '" + getClientId(client) + "' not found.");
  }
}

void
WebSocketsServerAsync::onTextReceived(AsyncWebSocketClient* client, const std::string& text) {
  IEntity::Unique entity;
  Request::Unique request;
  auto statusResult = serializer->deserialize(text, entity);
  if (statusResult->isOk()) {
    request = castToUnique<Request>(std::move(entity));
    if (request) {
      auto queueClient = findQueueClient(client);
      if (queueClient) {
        auto clientRequest = Request::makeShared(queueClient->getId(), std::move(request));
        statusResult = queueClient->sendMessage(clientRequest);
      } else {
        statusResult = StatusResult::makeUnique(StatusCode::InternalServerError,
          "Unable to find queue client '" + toString(client->id()) + "'.");
      }
    } else {
      statusResult = StatusResult::makeUnique(StatusCode::BadRequest,
        "Type '" + std::string(Request::TypeId) + "' was expected.");
    }
  }
  if (!statusResult->isOk()) {
    sendToClinet(client, *statusResult);
  }
}

void
WebSocketsServerAsync::onResponse(AsyncWebSocketClient* client, const Response& response) {
  sendToClinet(client, response);
}

void
WebSocketsServerAsync::onNotification(AsyncWebSocketClient* client, const Notification& notification) {
  sendToClinet(client, notification);
}
