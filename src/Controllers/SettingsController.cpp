#include "SettingsController.hpp"
#include "Services/IHttpServer.hpp"

void
SettingsController::onGetSettings() {
  /*
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
  }*/
}

void
SettingsController::onPutSettings() {
  /*
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
  */
}

void
SettingsController::registerOn(IHttpServer &server) {
  server.addGetHandler("/settings", [&]() { onGetSettings(); });
  server.addPutHandler("/settings", [&]() { onPutSettings(); });
}
