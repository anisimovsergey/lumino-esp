
#include "Services/HttpServer.hpp"

#include "Services/WiFiService.hpp"
#include "Controllers/NetworksController.hpp"
#include "Controllers/SettingsController.hpp"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

using namespace Services;
using namespace Controllers;

String network_ssid = "BTHub4-NC8S";
String network_pswd = "d5e89ca8cf";
const char* host = "esp8266fs";

Services::HttpServer server(80);

void setup(void){
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
