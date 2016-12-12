#include "Core/Logger.hpp"
#include "Core/MessageQueue.hpp"
#include "Core/StringFormat.hpp"
#include "Services/Display.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/WiFiScanner.hpp"
#include "Services/WebServerAsync.hpp"
#include "Services/Settings.hpp"
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
  Logger::message("Creating settings...");
  auto settings(Settings::makeShared());
  Logger::message("Creating a message queue...");
  auto messageQueue(MessageQueue::makeShared());
  Logger::message("Creating a display..");
  auto display(Display::makeShared(messageQueue));
  Logger::message("Creating a wifi manager...");
  auto wifiManager(WiFiManager::makeShared(settings, messageQueue));
  Logger::message("Creating a wifi scanner...");
  auto wiFiScanner(WiFiScanner::makeShared(messageQueue));
  Logger::message("Creating a context factory...");
  auto contextFactory(SerializationContextFactory::makeShared());
  Logger::message("Creating a serialization service...");
  auto serializationService(SerializationService::makeShared(contextFactory));
  Logger::message("Creating a Web server...");
  auto webServerAsync(WebServerAsync::makeShared(settings, messageQueue, serializationService));

  // Registering serializers
  Logger::message("Registering serializers...");
  serializationService->addSerializer(
    StatusResultSerializer::makeShared());
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
    NotificationSerializer::makeShared());
  serializationService->addSerializer(
    ObjectResultSerializer::makeShared());

  Logger::message("Starting wifi manager...");
  wifiManager->start();
  Logger::message("Starting Web server...");
  webServerAsync->start();

  // Adding servers to the loop
  Logger::message("Adding display...");
  loopedServices.push_back(display);
  Logger::message("Adding messqge queue...");
  loopedServices.push_back(messageQueue);
  Logger::message("Adding Web server...");
  loopedServices.push_back(webServerAsync);
  Logger::message("Adding wifi manager...");
  loopedServices.push_back(wifiManager);
  Logger::message("Adding wifi scaner...");
  loopedServices.push_back(wiFiScanner);
  Logger::message("Initialization finished, free heap size " + toString(ESP.getFreeHeap()) + " bytes.");
}

void loop(void){
  for(auto service : loopedServices) {
      service->loop();
  }
}
