#include "WebSocketsServerAsync.hpp"

#include <Core/Memory.hpp>
#include <Core/Logger.hpp>
#include <Core/IMessage.hpp>

using namespace Core;
using namespace Services;

const char* SenderId = "webSocketsServerAsync";
const char* FromClientTag = "fromClient";

WebSocketsServerAsync::WebSocketsServerAsync(int port,
  std::shared_ptr<IMessageQueue> messageQueue,
  std::shared_ptr<const Json::ISerializationService> serializer) :
  server(make_unique<WebSocketsServer>(port)), messageQueue(messageQueue),
  serializer(serializer) {
  server->begin();

  messageQueue->addMessageReceiver(SenderId, this);

  using namespace std::placeholders;
  server->onEvent(std::bind(&WebSocketsServerAsync::onSocketEvent, this,
    _1, _2, _3, _4));
}

WebSocketsServerAsync::~WebSocketsServerAsync() {

}

void
WebSocketsServerAsync::onSocketEvent(uint8_t num,
  WStype_t type, uint8_t * payload, size_t length) {

  if (type != WStype_TEXT)
    return;

  std::unique_ptr<IEntity> entity;
  std::shared_ptr<Request> request;
  auto statusResult = serializer->deserialize((char*)payload, entity);
  if (statusResult->isOk()) {
    request = dynamic_cast_to_shared<Request>(std::move(entity));
    if (request) {
      request->addTag(FromClientTag, String(num));
      statusResult = messageQueue->send(SenderId, request);
    }
  } else {
    statusResult = StatusResult::BadRequest("Type """ +
      String(Request::TypeId) + """ was expected.");
  }
  if (!statusResult->isOk()) {
    sendResponse(num, std::move(statusResult), request.get());
  }
}

void
WebSocketsServerAsync::sendResponse(uint8_t num,
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

  server->sendTXT(num, json);
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
    server->sendTXT(clientNumStr.toInt(), json);
  } else {
    // TODO : log error
  }
}

void
WebSocketsServerAsync::onNotification() {

}

void
WebSocketsServerAsync::onBroadcast() {

}


/*
void
WebSocketsServerAsync::onEventQueueBroadcast(message) {
  serializedMessage = serialize(message);
  server->broadcastTXT(serializedMessage);
}

void
WebSocketsServerAsync::onEventQueueMessage(message) {
  client = message.tags.get("client");
  serializedMessage = serialize(message);
  server->sendTXT(serializedMessage);
}
*/
