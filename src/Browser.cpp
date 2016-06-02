
#include "Core/Logger.hpp"
#include "Services/HttpServer.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/StatusCodeRegistry.hpp"
#include "Controllers/NetworksController.hpp"
#include "Controllers/SettingsController.hpp"
#include "Json/SerializationContextFactory.hpp"
#include "Json/SerializationService.hpp"
#include "Json/StatusSerializer.hpp"
#include "Json/ListSerializer.hpp"
#include "Json/NetworkSerializer.hpp"
#include "Json/SettingsSerializer.hpp"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

using namespace Core;
using namespace Json;
using namespace Services;
using namespace Controllers;

String network_ssid = "BTHub4-NC8S";
String network_pswd = "d5e89ca8cf";
const char* host = "esp8266fs";

std::list<std::shared_ptr<ILoopedService>> loopedServices;

void setup(void){
  // Initializing the logger
  Logger::initialize();

  // The old stuff
  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);
  //connectToWiFi();

  WiFi.softAP(host);
  //WiFi.softAPdisconnect(); // Disconnect and delete from memory.

  // Creating services
  std::shared_ptr<WiFiManager> wifiManager(
    new WiFiManager());
  std::shared_ptr<StatusCodeRegistry> codeRegistry(
    new StatusCodeRegistry());
  std::shared_ptr<SerializationContextFactory> contextFactory(
    new SerializationContextFactory());
  std::shared_ptr<SerializationService> serializationService(
    new SerializationService(contextFactory));

  std::shared_ptr<HttpServer> httpServer(new
    HttpServer(80, codeRegistry, serializationService));

  // Registering serializers
  serializationService->addSerializer(
    std::shared_ptr<StatusSerializer>(new StatusSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<ListSerializer>(new ListSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<NetworkSerializer>(new NetworkSerializer()));
  serializationService->addSerializer(
    std::shared_ptr<SettingsSerializer>(new SettingsSerializer()));

  // Registering controllers
  httpServer->addApiController(
    std::shared_ptr<NetworksController>(new NetworksController(wifiManager)));
  httpServer->addApiController(
    std::shared_ptr<SettingsController>(new SettingsController()));

  httpServer->start();

  // Adding servers to the loop
  loopedServices.push_back(httpServer);
}

void loop(void){
  for(auto service : loopedServices) {
      service->loop();
  }
}
