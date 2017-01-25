#include "Core/Logger.hpp"
#include "Core/MessageQueue.hpp"
#include "Core/StringFormat.hpp"
#include "Services/DisplayController.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/WiFiScanner.hpp"
#include "Services/WebServerAsync.hpp"
#include "Services/Settings.hpp"
#include "Serialization/SerializationService.hpp"
#include "Serialization/StatusSerializer.hpp"
#include "Serialization/ListSerializer.hpp"
#include "Serialization/NetworkSerializer.hpp"
#include "Serialization/SettingsSerializer.hpp"
#include "Serialization/ConnectionSerializer.hpp"
#include "Serialization/ContextFactory.hpp"
#include "Serialization/RequestSerializer.hpp"
#include "Serialization/ResponseSerializer.hpp"
#include "Serialization/EventSerializer.hpp"

using namespace Core;
using namespace Services;
using namespace Messaging;
using namespace Serialization;

ILogger::Shared logger;
std::list<IService::Shared> services;

void setup(void){

  logger = Logger::makeShared();

  // Creating services
  logger->message("Creating settings...");
  auto settings(Settings::makeShared());
  Logger::message("Creating a message queue...");
  auto messageQueue(MessageQueue::makeShared());
  Logger::message("Creating a display..");
  auto display(DisplayController::makeShared(messageQueue));
  Logger::message("Creating a wifi manager...");
  auto wifiManager(WiFiManager::makeShared(settings, messageQueue));
  logger->message("Creating a wifi scanner...");
  auto wiFiScanner(WiFiScanner::makeShared(messageQueue));
  logger->message("Creating a context factory...");
  auto contextFactory(ContextFactory::makeShared());
  logger->message("Creating a serialization service...");
  auto serializationService(SerializationService::makeShared(contextFactory));
  logger->message("Creating a Web server...");
  auto webServerAsync(WebServerAsync::makeShared(settings, messageQueue, serializationService));

  // Registering serializers
  logger->message("Registering serializers...");
  serializationService->addSerializer(
    StatusSerializer::makeShared());
  serializationService->addSerializer(
    ListSerializer<Models::Networks>::makeShared());
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
    EventSerializer::makeShared());

  logger->message("Starting wifi manager...");
  wifiManager->start();
  logger->message("Starting Web server...");
  webServerAsync->start();

  // Adding servers to the loop
  logger->message("Adding display...");
  services.push_back(display);
  logger->message("Adding messqge queue...");
  services.push_back(messageQueue);
  logger->message("Adding Web server...");
  services.push_back(webServerAsync);
  logger->message("Adding wifi manager...");
  services.push_back(wifiManager);
  logger->message("Adding wifi scaner...");
  services.push_back(wiFiScanner);
  logger->message("Initialization finished, free heap size " + toString(ESP.getFreeHeap()) + " bytes.");
}

void loop(void){
  for(auto service : services) {
      service->idle();
  }
}
