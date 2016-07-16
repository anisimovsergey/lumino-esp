#include "WebSocketsServerAsync.hpp"

#include <Core/Memory.hpp>
#include <Core/Logger.hpp>
#include <Core/IMessage.hpp>

using namespace Core;
using namespace Services;

WebSocketsServerAsync::WebSocketsServerAsync(int port,
  std::shared_ptr<IMessageQueue> messageQueue,
  std::shared_ptr<const Json::ISerializationService> serializer) :
  server(make_unique<WebSocketsServer>(port)), messageQueue(messageQueue),
  serializer(serializer) {
  server->begin();

  sender = eventQueue.addSender("webSocketsServerAsync",
    onResponse,
    onNotification);
  //eventQueue->addBroadcastListener(onBroadcastMessage);
  //eventQueue->addUnicastListener("webSocketsServerAsync", onUnicastMessage);
  //eventQueue->addResourceListener("/resource", onResourceMessage)

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
  auto statusResult = serializer->deserialize((char*)payload, entity);
  if (statusResult->isOk()) {
    if (entity->is<Message>()) {
      std::unique_ptr<Message> message(std::move(entity)->cast<Message>());
      message->addTag("fromClient", String(num));
      //statusResult = sender->send(message);
    } else {
      statusResult = StatusResult::BadRequest("Type Connection expected.");
    }
  }
  //sendResponse(httpRequest, *statusResult);
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
