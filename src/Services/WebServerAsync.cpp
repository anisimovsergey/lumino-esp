#include "WebServerAsync.hpp"

#include "Core/Memory.hpp"
#include <Core/Casting.hpp>
#include <Core/Format.hpp>

using namespace Core;
using namespace Messaging;
using namespace Serialization;
using namespace Services;

using namespace std::placeholders;

WebServerAsync::WebServerAsync(
  std::shared_ptr<const Settings> settings,
  IMessageQueue::Shared messageQueue,
  ISerializationService::Shared serializer) :
  settings(settings),
  messageQueue(messageQueue),
  serializer(serializer) {

  wsServer = std::move(Core::makeUnique<AsyncWebSocket>("/ws"));
  wsServer->onEvent(std::bind(&WebServerAsync::onSocketEvent, this,
    _1, _2, _3, _4, _5, _6));

  httpServer = std::move(Core::makeUnique<AsyncWebServer>(settings->getWebServerPort()));
  httpServer->addHandler(wsServer.get());
}

bool
WebServerAsync::isIntercepted(AsyncWebServerRequest *request) {
  return request->host() != settings->getLocalDomain().c_str();
}

void
WebServerAsync::redirectToSelf(AsyncWebServerRequest *request) {
  auto route = std::string("http://") + settings->getLocalDomain();
  request->redirect(route.c_str());
}

void
WebServerAsync::start() {
  SPIFFS.begin();
  httpServer->serveStatic("", SPIFFS, "");
  httpServer->onNotFound([&](AsyncWebServerRequest *request){
    if (isIntercepted(request)) {
      redirectToSelf(request);
    } else {
      request->send((int)StatusCode::NotFound);
    }
  });
  httpServer->begin();
}

void
WebServerAsync::onSocketEvent(AsyncWebSocket* server,
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
WebServerAsync::getClientId(AsyncWebSocketClient* client) {
  return "WebSocketsServer/" + toString(client->id());
}

QueueGenericClient::Shared
WebServerAsync::findQueueClient(AsyncWebSocketClient* client) {
  auto clientId = getClientId(client);
  for(auto client: queueClients) {
    if (client->getClientId() == clientId)
      return client;
  }
  return nullptr;
}

void
WebServerAsync::sendToClinet(AsyncWebSocketClient* client,
  const Core::IEntity& entity) {
  std::string json;
  auto status = serializer->serialize(entity, json);
  if (status.isOk()) {
    client->text(json.c_str());
  } else {
    status = serializer->serialize(status, json);
    if (status.isOk())
      client->text(json.c_str());
    else
      logger->error("Unable to seraile the response of type '" +
        status.getTypeId() + "'.");
  }
}

void
WebServerAsync::onClientConnected(AsyncWebSocketClient* client) {
  auto clientId = getClientId(client);
  auto queueClinet = messageQueue->createClient(clientId);
  queueClinet->setOnResponse([=](const Response& response){
    onResponse(client, response);
  });
  queueClinet->setOnEvent([=](const Event& event){
    onNotification(client, event);
  });
  queueClients.push_back(queueClinet);
  logger->message("Client '" + clientId + "' connected.");
}

void
WebServerAsync::onClientDisconnected(AsyncWebSocketClient* client) {
  auto queueClient = findQueueClient(client);
  if (queueClient) {
    messageQueue->removeClient(queueClient);
    queueClients.remove(queueClient);
    logger->message("Client '" + queueClient->getClientId() + "' disconnected.");
  } else {
    logger->error("Client '" + getClientId(client) + "' not found.");
  }
}

void
WebServerAsync::onTextReceived(AsyncWebSocketClient* client, const std::string& text) {
  IEntity::Unique entity;
  Request::Unique request;
  auto status = serializer->deserialize(text, entity);
  if (status.isOk()) {
    request = castToUnique<Request>(std::move(entity));
    if (request) {
      auto queueClient = findQueueClient(client);
      if (queueClient) {
        request->setSender(queueClient->getClientId());
        status = messageQueue->addRequest(std::move(request));
      } else {
        status = Status(StatusCode::InternalServerError,
          "Unable to find queue client '" + toString(client->id()) + "'.");
      }
    } else {
      status = Status(StatusCode::BadRequest, "Type '" +
        Request::TypeId() + "' was expected.");
    }
  }
  if (!status.isOk()) {
    sendToClinet(client, status);
  }
}

void
WebServerAsync::onResponse(AsyncWebSocketClient* client, const Response& response) {
  sendToClinet(client, response);
}

void
WebServerAsync::onNotification(AsyncWebSocketClient* client, const Event& event) {
  sendToClinet(client, event);
}
