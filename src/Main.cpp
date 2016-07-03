#include "Core/Logger.hpp"
#include "Services/HttpServerAsync.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/ObjectResultSender.hpp"
#include "Services/StatusResultSender.hpp"
#include "Services/RedirectResultSender.hpp"
#include "Json/SerializationService.hpp"
#include "Json/StatusResultSerializer.hpp"
#include "Json/ListSerializer.hpp"
#include "Json/NetworkSerializer.hpp"
#include "Json/SettingsSerializer.hpp"
#include "Json/ConnectionSerializer.hpp"
#include "Json/SerializationContextFactory.hpp"
#include "Controllers/NetworksController.hpp"
#include "Controllers/SettingsController.hpp"
#include "Controllers/ConnectionController.hpp"

#include <FS.h>

using namespace Core;
using namespace Json;
using namespace Services;
using namespace Controllers;

std::list<std::shared_ptr<ILoopedService>> loopedServices;

void setup(void){
  Logger::initialize();
  SPIFFS.begin();

  // Creating services
  auto wifiManager(std::make_shared<WiFiManager>());
  wifiManager->initialize();

  auto contextFactory(
    std::make_shared<SerializationContextFactory>());
  auto serializationService(
    std::make_shared<SerializationService>(contextFactory));
  auto httpServerAsync(
    std::make_shared<HttpServerAsync>(80, serializationService, wifiManager));

  // Registering serializers
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

  // Registering senders
  httpServerAsync->addHttpSender(
    std::make_shared<ObjectResultSender>(serializationService));
  httpServerAsync->addHttpSender(
    std::make_shared<StatusResultSender>(serializationService));
  httpServerAsync->addHttpSender(
    std::make_shared<RedirectResultSender>());

  // Registering controllers
  httpServerAsync->addApiController(
    std::make_shared<NetworksController>(wifiManager));
  httpServerAsync->addApiController(
    std::make_shared<SettingsController>(wifiManager));
  httpServerAsync->addApiController(
    std::make_shared<ConnectionController>(wifiManager));

  httpServerAsync->start();

  // Adding servers to the loop
  loopedServices.push_back(httpServerAsync);
  loopedServices.push_back(wifiManager);
}

void loop(void){
  for(auto service : loopedServices) {
      service->loop();
  }
}
