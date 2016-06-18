#include "Core/Logger.hpp"
#include "Services/HttpServerAsync.hpp"
#include "Services/WiFiManager.hpp"
#include "Json/SerializationService.hpp"
#include "Json/ActionResultSerializer.hpp"
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

  std::shared_ptr<HttpServerAsync> httpServerAsync(new
    HttpServerAsync(80, serializationService));

  // Registering serializers
  serializationService->addSerializer(
    std::shared_ptr<ActionResultSerializer>(new ActionResultSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<ListSerializer>(new ListSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<NetworkSerializer>(new NetworkSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<SettingsSerializer>(new SettingsSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<ConnectionSerializer>(new ConnectionSerializer()));

  //Registering controllers
  httpServerAsync->addApiController(
    std::shared_ptr<NetworksController>(new NetworksController(wifiManager)));
  httpServerAsync->addApiController(
    std::shared_ptr<SettingsController>(new SettingsController(wifiManager)));
  httpServerAsync->addApiController(
    std::shared_ptr<ConnectionController>(new ConnectionController(wifiManager)));

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
