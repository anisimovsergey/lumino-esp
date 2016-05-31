
#include "Core/Logger.hpp"
#include "Services/HttpServer.hpp"
#include "Services/WiFiService.hpp"
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

StatusCodeRegistry statusCodeRegistry;
SerializationContextFactory contextFactory;
SerializationService serializationService(contextFactory);

HttpServer server(80, statusCodeRegistry, serializationService);

WiFiService wifiService;

void setup(void){
  Logger::initialize();

  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);

  //connectToWiFi();

  WiFi.softAP(host);
  //WiFi.softAPdisconnect(); // Disconnect and delete from memory.

  // Registering serializers
  serializationService.addSerializer(
    std::shared_ptr<StatusSerializer>(new StatusSerializer()));
  serializationService.addSerializer(
    std::shared_ptr<ListSerializer>(new ListSerializer()));
  serializationService.addSerializer(
    std::shared_ptr<NetworkSerializer>(new NetworkSerializer()));
  serializationService.addSerializer(
    std::shared_ptr<SettingsSerializer>(new SettingsSerializer()));

  // Registering controllers
  server.addApiController(
    std::shared_ptr<NetworksController>(new NetworksController(wifiService)));
  server.addApiController(
    std::shared_ptr<SettingsController>(new SettingsController()));

  server.start();
}

void loop(void){
  server.loop();
}
