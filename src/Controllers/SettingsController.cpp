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
SettingsController::registerOn(IHttpServer &httpServer) {
  httpServer.addGetHandler("/settings", [&](IHttpRequest& request) {
    onGetSettings(request);
  });
  httpServer.addPutHandler("/settings", [&](IHttpRequest& request) {
    onPutSettings(request);
  });
}

void
SettingsController::onGetSettings(IHttpRequest& request) {
  Settings settings(
    wifiManager->getDeviceName()
  );
  request.createResponse(Status::Ok)->sendJson(settings);
}

void
SettingsController::onPutSettings(IHttpRequest& request) {
  std::shared_ptr<IEntity> entity;
  Status status = request.getJson(entity);
  if (status.isOk()) {
    Settings* settings = Settings::dynamicCast(entity.get());
    // TODO: Update device settings.
    if (settings != nullptr) {
      request.createResponse(Status::Ok)->sendJson(*settings);
    } else {
      request.createResponse(Status::IncorrectObjectType);
    }
  } else {
    request.createResponse(status);
  }
}
