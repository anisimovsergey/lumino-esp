
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include "Services/HttpServer.hpp"
#include "Controllers/NetworksController.hpp"
#include "Controllers/SettingsController.hpp"

#define MAX_CONNECTION_WAIT 10

String network_ssid = "BTHub4-NC8S";
String network_pswd = "d5e89ca8cf";
const char* host = "esp8266fs";

HttpServer server(80);

/*


bool disconnectFromFiFi() {
  if (WiFi.status() != WL_DISCONNECTED) {
    WiFi.disconnect();
    int i = 0;
    while ((WiFi.status() == WL_DISCONNECTED) && i < MAX_CONNECTION_WAIT) {
      delay(1000);
      i++;
    }
  }
}

bool connectToWiFi() {
  if (String(WiFi.SSID()) != network_ssid) {
    disconnectFromFiFi();
    WiFi.begin(network_ssid.c_str(), network_pswd.c_str());
    int i = 0;
    while ((WiFi.status() != WL_CONNECTED) && i < MAX_CONNECTION_WAIT) {
      delay(1000);
      i++;
    }
  }
}
*/

void setup(void){
  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);

  //connectToWiFi();

  WiFi.softAP(host);
  //WiFi.softAPdisconnect();

  NetworksController networksController;
  networksController.registerOn(server);

  SettingsController settingsController;
  settingsController.registerOn(server);

  server.start();
}

void loop(void){
  server.loop();
}
