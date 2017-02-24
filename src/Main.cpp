#include "Core/Format.hpp"
#include "Services/Logger.hpp"
#include "Services/DisplayController.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/WiFiScanner.hpp"
#include "Services/WebServerAsync.hpp"
#include "Services/Settings.hpp"
#include "Messaging/MessageQueue.hpp"
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

std::list<std::shared_ptr<IService>> services;
std::list<std::shared_ptr<IIdleService>> idleServices;

void setup(void){

  auto logger(std::make_shared<Services::Logger>());
  services.push_back(logger);

  // Creating services
  logger->message("Creating settings...");
  auto settings(std::make_shared<Settings>());
  logger->message("Creating a message queue...");
  auto messageQueue(std::make_shared<MessageQueue>(*logger));
  logger->message("Creating a display..");
  auto display(std::make_shared<DisplayController>(*messageQueue));
  logger->message("Creating a wifi manager...");
  auto wifiManager(std::make_shared<WiFiManager>(settings, *messageQueue));
  logger->message("Creating a wifi scanner...");
  auto wiFiScanner(std::make_shared<WiFiScanner>(*messageQueue));
  logger->message("Creating a context factory...");
  auto contextFactory(std::make_shared<ContextFactory>());
  logger->message("Creating a serialization service...");
  auto serializer(std::make_shared<SerializationService>(*contextFactory));
  logger->message("Creating a Web server...");
  auto webServerAsync(std::make_shared<WebServerAsync>(settings, *messageQueue, *serializer, *logger));

  // Registering serializers
  logger->message("Registering serializers...");
  serializer->addSerializer(std::make_unique<StatusSerializer>());
  serializer->addSerializer(std::make_unique<ListSerializer<Models::Networks>>());
  serializer->addSerializer(std::make_unique<NetworkSerializer>());
  serializer->addSerializer(std::make_unique<SettingsSerializer>());
  serializer->addSerializer(std::make_unique<ConnectionSerializer>());
  serializer->addSerializer(std::make_unique<RequestSerializer>());
  serializer->addSerializer(std::make_unique<ResponseSerializer>());
  serializer->addSerializer(std::make_unique<EventSerializer>());

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
  for(auto service : idleServices) {
      service->idle();
  }
}
