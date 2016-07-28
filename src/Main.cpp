#include "Core/Logger.hpp"
#include "Core/MessageQueue.hpp"
#include "Services/Display.hpp"
#include "Services/HttpServerAsync.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/WiFiScanner.hpp"
#include "Services/WebSocketsServerAsync.hpp"
#include "Json/SerializationService.hpp"
#include "Json/StatusResultSerializer.hpp"
#include "Json/ListSerializer.hpp"
#include "Json/NetworkSerializer.hpp"
#include "Json/SettingsSerializer.hpp"
#include "Json/ConnectionSerializer.hpp"
#include "Json/SerializationContextFactory.hpp"
#include "Json/RequestSerializer.hpp"
#include "Json/ResponseSerializer.hpp"
#include "Json/NotificationSerializer.hpp"
#include "Json/ObjectResultSerializer.hpp"
#include "Json/NetworksSerializer.hpp"

#include <FS.h>
#include <Adafruit_NeoPixel.h>

using namespace Core;
using namespace Json;
using namespace Services;

std::list<ILoopedService::Shared> loopedServices;

void setup(void){
  Logger::initialize();
  SPIFFS.begin();

  // Creating services
  Logger::message("Creating the message queue...");
  auto messageQueue(MessageQueue::makeShared());
  Logger::message("Creating the display..");
  auto display(Display::makeShared(messageQueue));
  Logger::message("Creating the wifi manager...");
  auto wifiManager(WiFiManager::makeShared(messageQueue));
  Logger::message("Creating the wifi scanner...");
  auto wiFiScanner(WiFiScanner::makeShared(messageQueue));
  Logger::message("Creating the context factory...");
  auto contextFactory(SerializationContextFactory::makeShared());
  Logger::message("Creating the serialization service...");
  auto serializationService(SerializationService::makeShared(contextFactory));
  Logger::message("Creating the creating HTTP server...");
  auto httpServerAsync(HttpServerAsync::makeShared(80, wifiManager));
  Logger::message("Creating creating Web Sockets server...");
  auto webSocketsServerAsync(WebSocketsServerAsync::makeShared(messageQueue, serializationService));
  httpServerAsync->server->addHandler(webSocketsServerAsync->server.get());

  // Registering serializers
  Logger::message("Registering serializers...");
  serializationService->addSerializer(
    StatusResultSerializer::makeShared());
  serializationService->addSerializer(
    ListSerializer::makeShared());
  serializationService->addSerializer(
    NetworkSerializer::makeShared());
  serializationService->addSerializer(
    SettingsSerializer::makeShared());
  serializationService->addSerializer(
    ConnectionSerializer::makeShared());
  serializationService->addSerializer(
    RequestSerializer::makeShared());
  serializationService->addSerializer(
    ResponseSerializer::makeShared());
  serializationService->addSerializer(
    NotificationSerializer::makeShared());
  serializationService->addSerializer(
    ObjectResultSerializer::makeShared());
  serializationService->addSerializer(
    NetworksSerializer::makeShared());

  Logger::message("Starting wifi manager...");
  wifiManager->start();
  Logger::message("Starting http server...");
  httpServerAsync->start();
  Logger::message("Starting websocket server server...");
  webSocketsServerAsync->start();

  // Adding servers to the loop
  Logger::message("Adding services to the loop...");
  loopedServices.push_back(display);
  loopedServices.push_back(messageQueue);
  loopedServices.push_back(httpServerAsync);
  loopedServices.push_back(wifiManager);
  loopedServices.push_back(wiFiScanner);
  loopedServices.push_back(webSocketsServerAsync);
  Logger::message("Initialization finished, free heap size " + String(ESP.getFreeHeap()) + " bytes.");
}

void loop(void){
  for(auto service : loopedServices) {
      service->loop();
  }
}
