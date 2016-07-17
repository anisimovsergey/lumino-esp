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

  messageSender = messageQueue->addSender(SenderId,
    std::bind(&WebSocketsServerAsync::onResponse, this),
    std::bind(&WebSocketsServerAsync::onNotification, this));
  messageQueue->addBroadcastListener(
    std::bind(&WebSocketsServerAsync::onBroadcastMessage, this));

  using namespace std::placeholders;
  server->onEvent(std::bind(&WebSocketsServerAsync::onSocketEvent, this,
    _1, _2, _3, _4));
}

WebSocketsServerAsync::~WebSocketsServerAsync() {

}

template<class Derived, class Base, class Del>
std::unique_ptr<Derived, Del>
dynamic_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
   if (Derived *result = Derived::cast(p.get())){
        p.release();
        return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}

template<class Derived, class Base, class Del>
std::shared_ptr<Derived>
dynamic_shared_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
   if (Derived *result = Derived::cast(p.get())){
        p.release();
        return std::shared_ptr<Derived>(result);
    }
    return std::shared_ptr<Derived>(nullptr);
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
    request = dynamic_shared_ptr_cast<Request>(std::move(entity));
    if (request) {
      request->addTag(FromClientTag, String(num));
      statusResult = messageSender->send(request);
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
    response = make_unique<Response>(std::move(result),
      request->getMessageType(), request->getResource());
  } else {
    response = make_unique<Response>(std::move(result));
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
WebSocketsServerAsync::onResponse() {

}

void
WebSocketsServerAsync::onNotification() {

}

void
WebSocketsServerAsync::onBroadcastMessage() {

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
