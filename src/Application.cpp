#include "Application.hpp"

#include "Core/Format.hpp"
#include "Serialization/StatusSerializer.hpp"
#include "Serialization/ListSerializer.hpp"
#include "Serialization/NetworkSerializer.hpp"
#include "Serialization/SettingsSerializer.hpp"
#include "Serialization/ConnectionSerializer.hpp"
#include "Serialization/ContextFactory.hpp"
#include "Serialization/RequestSerializer.hpp"
#include "Serialization/ResponseSerializer.hpp"
#include "Serialization/EventSerializer.hpp"
#include "Serialization/ColorSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Services;
using namespace Serialization;

void
Application::setup() {
  createServices();
  registerSerializers();
  logger->message("Initialized, free heap: " + toString(ESP.getFreeHeap()) + " bytes.");
}

void
Application::createServices() {
  logger = std::make_unique<Logger>();
  logger->message("Creating a message queue...");
  messageQueue = std::make_unique<MessageQueue>();
  logger->message("Creating a display...");
  display = std::make_unique<DisplayController>(*messageQueue, *logger);
  logger->message("Creating settings...");
  settings = std::make_unique<SettingsController>(*messageQueue, *logger);
  logger->message("Creating an update controller (OTA) ...");
  updater = std::make_unique<UpdateController>(*messageQueue, *logger);
  logger->message("Creating a wifi manager...");
  wifiManager = std::make_unique<WiFiManager>(*messageQueue);
  logger->message("Creating a wifi scanner...");
  wifiScanner = std::make_unique<WiFiScanner>(*messageQueue);
  logger->message("Creating a context factory...");
  contextFactory = std::make_unique<ContextFactory>();
  logger->message("Creating a serialization service...");
  serializer = std::make_unique<SerializationService>(*contextFactory);
  logger->message("Creating a Web server...");
  webServerAsync = std::make_unique<WebServerAsync>(*messageQueue, *serializer, *logger);
}

void
Application::registerSerializers() {
  logger->message("Registering serializers...");
  serializer->addSerializer(std::make_unique<StatusSerializer>());
  serializer->addSerializer(std::make_unique<ListSerializer<Models::Networks>>());
  serializer->addSerializer(std::make_unique<NetworkSerializer>());
  serializer->addSerializer(std::make_unique<SettingsSerializer>());
  serializer->addSerializer(std::make_unique<ConnectionSerializer>());
  serializer->addSerializer(std::make_unique<RequestSerializer>());
  serializer->addSerializer(std::make_unique<ResponseSerializer>());
  serializer->addSerializer(std::make_unique<EventSerializer>());
  serializer->addSerializer(std::make_unique<ColorSerializer>());
}

void
Application::loop() {
  messageQueue->idle();
  wifiManager->idle();
  updater->idle();
}
