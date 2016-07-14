#include "WebSocketsServerAsync.hpp"

#include <Core/Memory.hpp>
#include <Core/Logger.hpp>

using namespace Core;
using namespace Services;

WebSocketsServerAsync::WebSocketsServerAsync(int port) :
  server(make_unique<WebSocketsServer>(port)) {
  server->begin();

  //eventQueue->addBroadcastListener(onEventQueueBroadcast);
  //eventQueue->addUnicastListener("webSocketsServerAsync", onEventQueueMessage);

  using namespace std::placeholders;
  server->onEvent(std::bind(&WebSocketsServerAsync::onSocketEvent, this,
    _1, _2, _3, _4));
}

WebSocketsServerAsync::~WebSocketsServerAsync() {

}

void
WebSocketsServerAsync::onSocketEvent(uint8_t num,
  WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    Logger::message((char*)payload);
  }
/*
  if (type == WStype_TEXT) {
    // client - num, text - payload
    message = new Message();
    message.source = "webSocketsServerAsync";
    message.tags.add("client", num);
    messageQueue.sendMessage(message);
  }*/
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
