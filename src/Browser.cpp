
#include "Core/Logger.hpp"
#include "Services/HttpServer.hpp"
#include "Services/WiFiService.hpp"
#include "Services/StatusCodeRegistry.hpp"
#include "Controllers/NetworksController.hpp"
#include "Controllers/SettingsController.hpp"
#include "Json/SerializationContextFactory.hpp"
#include "Json/SerializationService.hpp"

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

void setup(void){
  Logger::initialize();
  
  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);

  //connectToWiFi();

  WiFi.softAP(host);
  //WiFi.softAPdisconnect(); // Disconnect and delete from memory.

  WiFiService wifiService;

  NetworksController networksController(wifiService);
  networksController.registerOn(server);

  SettingsController settingsController;
  settingsController.registerOn(server);

  server.start();
}

void loop(void){
  server.loop();
}
