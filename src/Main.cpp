#include "Core/Logger.hpp"
#include "Services/HttpServer.hpp"
#include "Services/WiFiManager.hpp"
#include "Json/SerializationService.hpp"
#include "Json/StatusSerializer.hpp"
#include "Json/ListSerializer.hpp"
#include "Json/NetworkSerializer.hpp"
#include "Json/SettingsSerializer.hpp"
#include "Json/ConnectionSerializer.hpp"
#include "Json/SerializationContextFactory.hpp"
#include "Controllers/NetworksController.hpp"
#include "Controllers/SettingsController.hpp"
#include "Controllers/ConnectionController.hpp"

using namespace Core;
using namespace Json;
using namespace Services;
using namespace Controllers;

std::list<std::shared_ptr<ILoopedService>> loopedServices;

void setup(void){
  Logger::initialize();

  // Creating services
  std::shared_ptr<WiFiManager> wifiManager(
    new WiFiManager());
  wifiManager->initialize();

  std::shared_ptr<SerializationContextFactory> contextFactory(
    new SerializationContextFactory());
  std::shared_ptr<SerializationService> serializationService(
    new SerializationService(contextFactory));

  std::shared_ptr<HttpServer> httpServer(new
    HttpServer(80, serializationService));

  // Registering serializers
  serializationService->addSerializer(
    std::shared_ptr<StatusSerializer>(new StatusSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<ListSerializer>(new ListSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<NetworkSerializer>(new NetworkSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<SettingsSerializer>(new SettingsSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<ConnectionSerializer>(new ConnectionSerializer()));

  // Registering controllers
  httpServer->addApiController(
    std::shared_ptr<NetworksController>(new NetworksController(wifiManager)));
  httpServer->addApiController(
    std::shared_ptr<SettingsController>(new SettingsController(wifiManager)));
  httpServer->addApiController(
    std::shared_ptr<ConnectionController>(new ConnectionController(wifiManager)));

  httpServer->start();

  // Adding servers to the loop
  loopedServices.push_back(wifiManager);
}

void loop(void){
  for(auto service : loopedServices) {
      service->loop();
  }
}
