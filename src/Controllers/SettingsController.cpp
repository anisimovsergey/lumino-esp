#include "SettingsController.hpp"

#include "Core/ActionResult.hpp"
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
  httpServer.addPutHandler("/settings", [&](IHttpRequest& request,
    const Core::IEntity& entity) {
    onPutSettings(request, entity);
  });
}

std::shared_ptr<Core::ActionResult>
SettingsController::onGetSettings(IHttpRequest& request) {
  std::shared_ptr<Settings> settings(new Settings(
    wifiManager->getDeviceName()
  ));
  ActionResult::Success(settings);
}

std::shared_ptr<Core::ActionResult>
SettingsController::onPutSettings(
  IHttpRequest& request, const Core::IEntity& entity) {
  auto settings = Settings::dynamicCast(&entity);
  if (settings == nullptr)
    return ActionResult::IncorrectObjectType();

  // TODO: Update device settings.
  ActionResult::Success();
}
