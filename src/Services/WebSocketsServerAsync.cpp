#include "WebSocketsServerAsync.hpp"

#include <Core/Memory.hpp>
#include <Core/Logger.hpp>
#include <Core/IMessage.hpp>

using namespace Core;
using namespace Services;
using namespace std::placeholders;

namespace {
  const char* SenderId = "WebSocketsServerAsync";
  const char* FromClientTag = "fromClient";
}

WebSocketsServerAsync::WebSocketsServerAsync(int port,
  std::shared_ptr<IMessageQueue> messageQueue,
  std::shared_ptr<const Json::ISerializationService> serializer) :
  server(make_unique<AsyncWebSocket>("/ws")), messageQueue(messageQueue),
  serializer(serializer) {

/*
  auto messageSender = std::make_shared<MessageSender>(SenderId,
    std::bind(&WebSocketsServerAsync::onResponse, this, _1),
    std::bind(&WebSocketsServerAsync::onNotification, this, _1));
  messageQueue->addMessageSender(messageSender);

  auto messageListener = std::make_shared<MessageListener>(
    std::bind(&WebSocketsServerAsync::onBroadcast, this, _1));
  messageQueue->addMessageListener(messageListener);
  */

  server->onEvent(std::bind(&WebSocketsServerAsync::onSocketEvent, this,
    _1, _2, _3, _4, _5, _6));
}

WebSocketsServerAsync::~WebSocketsServerAsync() {

}

void
WebSocketsServerAsync::onSocketEvent(AsyncWebSocket* server,
  AsyncWebSocketClient* client, AwsEventType type, void * arg,
  uint8_t *data, size_t len) {

  if (type == WS_EVT_CONNECT) {
    auto queueClinet = WebSocketQueueClient::makeShared(client);
    messageQueue->addClient(queueClinet);
    clients.push_back(queueClinet);
  }

  if (type == WS_EVT_DISCONNECT) {
    auto queueClient = findQueueClient(client);
    if (queueClient)
      cleants.remove(queueClient);
  }

  if (type != WS_EVT_DATA)
    return;

  AwsFrameInfo * info = (AwsFrameInfo*)arg;
  if (!(info->final && info->index == 0 && info->len == len))
    return;

  if (info->opcode != WS_TEXT)
    return;

  data[len] = 0;
  String text((char*)data);

  std::unique_ptr<IEntity> entity;
  std::shared_ptr<Request> request;
  auto statusResult = serializer->deserialize(text, entity);
  if (statusResult->isOk()) {
    request = castToShared<Request>(std::move(entity));
    if (request) {
      auto queueClient = findQueueClient(client);
      if (queueClient)
        statusResult = queueClient.send(request);
      else
        statusResult = StatusResult::InternalServerError(
          "Unable to find queue client '" + client->id() +"'.");
    } else {
      statusResult = StatusResult::BadRequest(
        "Type '" + String(Request::TypeId) + "' was expected.");
    }
  }
  if (!statusResult->isOk()) {
    sendResponse(client->id(), *statusResult);
  }
}

void
WebSocketsServerAsync::sendResponse(uint32_t num,
  const Core::StatusResult& result) {
  String json;
  auto status = serializer->serialize(result, json);
  if (status->isOk()) {
    server->text(num, json);
  } else {
    Logger::error("Unbale to seraile the response.");
  }
}

void
WebSocketsServerAsync::sendResponse(const Core::Message& message, String& text) {
  auto clientNumStr = message.getTag(FromClientTag);
  if (clientNumStr.length() == 0) {
    auto clientNum = clientNumStr.toInt();
    if (server->hasClient(clientNum)) {
      server->text(clientNumStr.toInt(), text);
    } else {
      Logger::error("Client + '" + clientNumStr + "' does not exist.");
    }
  } else {
    Logger::error("Client is not specified.");
  }
}

void
WebSocketsServerAsync::onResponse(std::shared_ptr<Response> response) {
  String json;
  auto status = serializer->serialize(*response, json);
  if (status->isOk()) {
    sendResponse(*response, json);
  } else {
    Logger::error("Unbale to seraile the response.");
  }
}

void
WebSocketsServerAsync::onNotification(std::shared_ptr<Core::Notification> notification) {
  String json;
  auto status = serializer->serialize(*notification, json);
  if (status->isOk()) {
    sendResponse(*notification, json);
  } else {
    Logger::error("Unbale to seraile the notification.");
  }
}

void
WebSocketsServerAsync::onBroadcast(std::shared_ptr<Core::Notification> notification) {
  String json;
  auto status = serializer->serialize(*notification, json);
  if (status->isOk()) {
    server->textAll(json);
  } else {
    Logger::error("Unbale to seraile the notification.");
  }
}
