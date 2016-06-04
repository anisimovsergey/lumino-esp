#include "SettingsController.hpp"

#include "Core/Status.hpp"
#include "Core/Logger.hpp"
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
  Logger::message("In on get settings...");
  Settings settings(
    wifiManager->getDeviceName(),
    wifiManager->getNetwork(), "",
    wifiManager->isConnected()
  );
  Logger::message("Settings constructed");
  httpServer.sendJson(settings);
}

void
SettingsController::onPutSettings(Services::IHttpServer& httpServer) {
  std::shared_ptr<IEntity> entity;
  Status status = httpServer.getJson(entity);
  if (status.isOk()) {
    Logger::message("Settings json is OK.");
    Settings* settings = Settings::dynamicCast(entity.get());
    Logger::message("Entity casted to settings");
    if (settings != nullptr) {
      Logger::message("Sending settings");
      httpServer.sendJson(*settings);
    } else {
      httpServer.sendJson(Status::IncorrectObjectType);
    }
  } else {
    httpServer.sendJson(status);
  }
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
