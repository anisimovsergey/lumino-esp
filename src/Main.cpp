#include "Core/Logger.hpp"
#include "Core/MessageQueue.hpp"
#include "Services/Display.hpp"
#include "Services/HttpServerAsync.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/ObjectResultSender.hpp"
#include "Services/StatusResultSender.hpp"
#include "Services/RedirectResultSender.hpp"
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

#include <FS.h>
#include <Adafruit_NeoPixel.h>

using namespace Core;
using namespace Json;
using namespace Services;

std::list<std::shared_ptr<ILoopedService>> loopedServices;

void setup(void){
  Logger::initialize();
  SPIFFS.begin();

  // Creating services
  Logger::message("Creating the message queue...");
  auto messageQueue(std::make_shared<MessageQueue>());
  Logger::message("Creating the display..");
  auto display(std::make_shared<Display>());
  Logger::message("Creating the wifi manager...");
  auto wifiManager(std::make_shared<WiFiManager>(messageQueue));
  wifiManager->initialize();

  Logger::message("Creating the context factory...");
  auto contextFactory(
    std::make_shared<SerializationContextFactory>());
  Logger::message("Creating the serialization service...");
  auto serializationService(
    std::make_shared<SerializationService>(contextFactory));
  Logger::message("Creating the creating HTTP server...");
  auto httpServerAsync(
    std::make_shared<HttpServerAsync>(80, serializationService, wifiManager));
  Logger::message("Creating creating Web Sockets server...");
  auto webSocketsServerAsync(
    std::make_shared<WebSocketsServerAsync>(81, messageQueue, serializationService));

  // Registering serializers
  Logger::message("Registering serializers...");
  serializationService->addSerializer(
    std::make_shared<StatusResultSerializer>());
  serializationService->addSerializer(
    std::make_shared<ListSerializer>());
  serializationService->addSerializer(
    std::make_shared<NetworkSerializer>());
  serializationService->addSerializer(
    std::make_shared<SettingsSerializer>());
  serializationService->addSerializer(
    std::make_shared<ConnectionSerializer>());
  serializationService->addSerializer(
    std::make_shared<RequestSerializer>());
  serializationService->addSerializer(
    std::make_shared<ResponseSerializer>());

  // Registering senders
  Logger::message("Registering services...");
  httpServerAsync->addHttpSender(
    std::make_shared<ObjectResultSender>(serializationService));
  httpServerAsync->addHttpSender(
    std::make_shared<StatusResultSender>(serializationService));
  httpServerAsync->addHttpSender(
    std::make_shared<RedirectResultSender>());

  Logger::message("Starting http server...");
  httpServerAsync->start();
  Logger::message("Starting websocket server server...");
  webSocketsServerAsync->start();

  // Adding servers to the loop
  Logger::message("Adding services to the loop...");
  loopedServices.push_back(messageQueue);
  loopedServices.push_back(httpServerAsync);
  loopedServices.push_back(wifiManager);
  loopedServices.push_back(webSocketsServerAsync);
  Logger::message("Initialization finished.");
}

void loop(void){
  for(auto service : loopedServices) {
      service->loop();
  }
}
