#include "WebServerAsync.hpp"

#include "Core/Memory.hpp"
#include <Core/Format.hpp>

using namespace Core;
using namespace Messaging;
using namespace Serialization;
using namespace Services;

namespace {
  /** IP to String? */
  String toStringIp(IPAddress ip) {
    String res = "";
    for (int i = 0; i < 3; i++) {
      res += String((ip >> (8 * i)) & 0xFF) + ".";
    }
    res += String(((ip >> 8 * 3)) & 0xFF);
    return res;
  }
}

WebServerAsync::WebServerAsync(
  IMessageQueue& messageQueue,
  ISerializationService& serializer,
  ILogger& logger) :
  messageQueue(messageQueue),
  serializer(serializer),
  logger(logger) {

  wsServer = std::move(std::make_unique<AsyncWebSocket>("/ws"));
  wsServer->onEvent([=](AsyncWebSocket* server, AsyncWebSocketClient* client,
    AwsEventType type, void* arg, uint8_t *data, size_t len) {
    WebServerAsync::onSocketEvent(server, client, type, arg, data, len);
  });

  httpServer = std::move(std::make_unique<AsyncWebServer>(80));
  httpServer->addHandler(wsServer.get());
}

std::string
WebServerAsync::getLocalDomain() const {
  return toStringIp(WiFi.softAPIP()).c_str();
}

bool
WebServerAsync::isIntercepted(AsyncWebServerRequest *request) {
  return request->host() != getLocalDomain().c_str();
}

void
WebServerAsync::redirectToSelf(AsyncWebServerRequest *request) {
  auto route = std::string("http://") + getLocalDomain();
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

Messaging::QueueGenericClient*
WebServerAsync::findQueueClient(AsyncWebSocketClient* client) {
  auto clientId = getClientId(client);
  for(const auto& client: queueClients) {
    if (client->getClientId() == clientId)
      return client.get();
  }
  return nullptr;
}

void
WebServerAsync::sendToClinet(AsyncWebSocketClient* client,
  const Core::IEntity& entity) {
  std::string json;
  auto status = serializer.serialize(entity, json);
  if (status.isOk()) {
    client->text(json.c_str());
  } else {
    status = serializer.serialize(status, json);
    if (status.isOk())
      client->text(json.c_str());
    else
      logger.error("Unable to seraile the response of type '" +
        status.getTypeId() + "'.");
  }
}

void
WebServerAsync::onClientConnected(AsyncWebSocketClient* client) {
  auto clientId = getClientId(client);
  auto queueClinet = messageQueue.createClient(clientId);
  queueClinet->setOnResponse([=](const Response& response){
    onResponse(client, response);
  });
  queueClinet->setOnEvent([=](const Event& event){
    onNotification(client, event);
  });
  queueClients.push_back(std::move(queueClinet));
  logger.message("Client '" + clientId + "' connected.");
}

void
WebServerAsync::onClientDisconnected(AsyncWebSocketClient* client) {
  auto clientId = getClientId(client);
  for (auto iter = queueClients.begin(); iter != queueClients.end(); iter++) {
     if (iter->get()->getClientId() == clientId) {
       queueClients.erase(iter);
       logger.message("Client '" + clientId + "' disconnected.");
       return;
     }
  }
  logger.error("Client '" + clientId + "' not found.");
}

void
WebServerAsync::onTextReceived(AsyncWebSocketClient* client, const std::string& text) {
  std::unique_ptr<IEntity> entity;
  std::unique_ptr<Request> request;
  auto status = serializer.deserialize(text, entity);
  if (status.isOk()) {
    request = castToUnique<Request>(std::move(entity));
    if (request) {
      auto queueClient = findQueueClient(client);
      if (queueClient) {
        request->setSender(queueClient->getClientId());
        status = messageQueue.addRequest(std::move(request));
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
