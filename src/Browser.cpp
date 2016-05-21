
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>

#define MAX_CONNECTION_WAIT 10

String network_ssid = "BTHub4-NC8S";
String network_pswd = "d5e89ca8cf";
const char* host = "esp8266fs";

ESP8266WebServer server(80);

String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path){

  if(path.endsWith("/"))
    path += "index.html";

  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){

    String contentType = getContentType(path);
    if(SPIFFS.exists(pathWithGz))
      path = pathWithGz;

    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

String getEncryptionType(int thisType) {
  switch (thisType) {
    case ENC_TYPE_WEP:
      return "WEP";
    case ENC_TYPE_TKIP:
      return "WPA";
    case ENC_TYPE_CCMP:
      return "WPA2";
    case ENC_TYPE_NONE:
      return "None";
    case ENC_TYPE_AUTO:
      return "Auto";
  }
}

void onGetWiFiNetworks() {
  int networksCount = WiFi.scanNetworks();
  if (networksCount == -1) {
    String json = "{";
    json += "\"type\": \"error\",";
    json += "\"status\": \"500\",";
    json += "\"code\": \"UnableToScanWiFiNetwors\",";
    json += "\"title\": \"Unable to scan WiFi networks.\",";
    json += "}";
    server.send(500, "text/json", json);
  } else {
    String json = "[";
    for (int networkNum = 0; networkNum < networksCount; networkNum++) {
      json += "{";
      json += "\"ssid\": \"" + WiFi.SSID(networkNum) + "\",";
      json += "\"rssi\": " + String(WiFi.RSSI(networkNum)) + ",";
      json += "\"encryption\": \"" + getEncryptionType(WiFi.encryptionType(networkNum)) + "\"";
      json += "}";
      if (networkNum < networksCount - 1)
        json += ",";
    }
    json += "]";
    server.send(200, "text/json", json);
  }
}

String getSettingsJson() {
  const int BUFFER_SIZE = JSON_OBJECT_SIZE(5);
  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["name"] = host;
  root["wifi_network"] = WiFi.SSID();
  root["wifi_password"] = "";
  root["connected"] = WiFi.status() == WL_CONNECTED;

  String json;
  root.printTo(json);
  return json;
}

void onGetSettings() {
  server.send(200, "text/json", getSettingsJson());
}

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

void onPutSettings() {

  const size_t BUFFER_SIZE = JSON_OBJECT_SIZE(5);
  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;

  String request = server.arg("plain");
  JsonObject& root = jsonBuffer.parseObject(request);

  if (!root.success()) {
    String json = "{";
    json += "\"type\": \"error\",";
    json += "\"status\": \"500\",";
    json += "\"code\": \"UnableToParseJson\",";
    json += "\"title\": \"Unable to parse JSON.\",";
    json += "\"data\": " + request;
    json += "}";
    server.send(500, "text/json", json);
    return;
  }

  if (root["connected"]) {
    network_ssid = (const char*)root["wifi_network"];
    network_pswd = (const char*)root["wifi_password"];
  }

  if (WiFi.status() == WL_CONNECTED)
    disconnectFromFiFi();
  else {
    connectToWiFi();
  }

  server.send(202, "text/json", getSettingsJson());
}

void setup(void){
  SPIFFS.begin();

  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);

  connectToWiFi();

  WiFi.softAP(host);
  //WiFi.softAPdisconnect();

  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  server.on("/wifi_networks", HTTP_GET, []() { onGetWiFiNetworks(); });
  server.on("/settings", HTTP_GET, []() { onGetSettings(); });
  server.on("/settings", HTTP_PUT, []() { onPutSettings(); });

  server.begin();
}

void loop(void){
  server.handleClient();
}
