#include "WebSocketsServerAsync.hpp"

#include <Core/Memory.hpp>
#include <Core/Logger.hpp>
#include <Core/IMessage.hpp>

using namespace Core;
using namespace Services;
using namespace std::placeholders;

const char* SenderId = "webSocketsServerAsync";
const char* FromClientTag = "fromClient";

WebSocketsServerAsync::WebSocketsServerAsync(int port,
  std::shared_ptr<IMessageQueue> messageQueue,
  std::shared_ptr<const Json::ISerializationService> serializer) :
  server(make_unique<AsyncWebSocket>("/ws")), messageQueue(messageQueue),
  serializer(serializer) {

  auto messageSender = std::make_shared<MessageSender>(SenderId,
    std::bind(&WebSocketsServerAsync::onResponse, this, _1),
    std::bind(&WebSocketsServerAsync::onNotification, this, _1));
  messageQueue->addMessageSender(messageSender);

  auto messageListener = std::make_shared<MessageListener>(
    std::bind(&WebSocketsServerAsync::onBroadcast, this, _1));
  messageQueue->addMessageListener(messageListener);

  server->onEvent(std::bind(&WebSocketsServerAsync::onSocketEvent, this,
    _1, _2, _3, _4, _5, _6));
}

WebSocketsServerAsync::~WebSocketsServerAsync() {

}

void
WebSocketsServerAsync::onSocketEvent(AsyncWebSocket* server,
  AsyncWebSocketClient* client, AwsEventType type, void * arg,
  uint8_t *data, size_t len) {

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
    request = dynamic_cast_to_shared<Request>(std::move(entity));
    if (request) {
      request->addTag(FromClientTag, String(client->id()));
      statusResult = messageQueue->send(SenderId, request);
    } else {
      statusResult = StatusResult::BadRequest("Type '" +
        String(Request::TypeId) + "' was expected.");
    }
  }
  if (!statusResult->isOk()) {
    sendResponse(client->id(), std::move(statusResult), request.get());
  }
}

void
WebSocketsServerAsync::sendResponse(uint32_t num,
  std::unique_ptr<Core::StatusResult>&& result,
  const Core::Request* request) {

  std::unique_ptr<Response> response;
  if (request != nullptr) {
    response = make_unique<Response>(
      request->getActionType(),
      request->getResource(),
      std::move(result));
  } else {
    response = make_unique<Response>(
      ActionType::Unknown, "", std::move(result));
  }

  String json;
  auto status = serializer->serialize(*response, json);
  if (!status->isOk()) {
    Logger::error("Unbale to seraile the response.");
    return;
  }

  server->text(num, json);
}

void
WebSocketsServerAsync::onResponse(std::shared_ptr<Response> response) {
  String json;
  auto status = serializer->serialize(*response, json);
  if (!status->isOk()) {
    Logger::error("Unbale to seraile the response.");
    return;
  }

  auto clientNumStr = response->getTag(FromClientTag);
  if (clientNumStr != "") {
    server->text(clientNumStr.toInt(), json);
  } else {
    // TODO : log error
  }
}

void
WebSocketsServerAsync::onNotification(std::shared_ptr<Core::Notification> notification) {
  String json;
  auto status = serializer->serialize(*notification, json);
  if (!status->isOk()) {
    serializer->serialize(*status, json);
    Logger::error("Unbale to seraile the response. " + json);
    return;
  }

  auto clientNumStr = notification->getTag(FromClientTag);
  Logger::error("clientNumStr" + clientNumStr);
  if (clientNumStr != "") {
    server->text(clientNumStr.toInt(), json);
  } else {
    // TODO : log error
  }
}

void
WebSocketsServerAsync::onBroadcast(std::shared_ptr<Core::Notification> notification) {
  String json;
  auto status = serializer->serialize(*notification, json);
  if (!status->isOk()) {
    Logger::error("Unbale to seraile the response.");
    return;
  }

  server->textAll(json);
}
