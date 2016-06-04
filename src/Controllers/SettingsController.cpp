#include "SettingsController.hpp"

#include "Core/Status.hpp"
#include "Models/Settings.hpp"
#include "Services/IHttpServer.hpp"

using namespace Core;
using namespace Services;
using namespace Models;
using namespace Controllers;

SettingsController::SettingsController(
  std::shared_ptr<const IWiFiManager> wifiManager) :
  wifiManager(wifiManager) {
}

void
SettingsController::onGetSettings(Services::IHttpServer& httpServer) {
  Settings settings(
    wifiManager->getDeviceName(),
    wifiManager->getNetwork(), "",
    wifiManager->isConnected()
  );
  httpServer.sendJson(settings);
}

void
SettingsController::onPutSettings(Services::IHttpServer& httpServer) {
  std::shared_ptr<IEntity> entity;
  Status status = httpServer.getJson(entity);
  if (status.isOk()) {
    Settings* settings = Settings::dynamicCast(entity.get());
    if (settings != nullptr) {
      httpServer.sendJson(*settings);
    } else {
      httpServer.sendJson(Status::IncorrectObjectType);
    }
  } else {
    httpServer.sendJson(status);
  }
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
SettingsController::registerOn(IHttpServer &httpServer) {
  httpServer.addGetHandler("/settings", [&]() {
    onGetSettings(httpServer);
  });
  httpServer.addPutHandler("/settings", [&]() {
    onPutSettings(httpServer);
  });
}
