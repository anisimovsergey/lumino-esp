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
    return onGetSettings(request);
  });
  httpServer.addPutHandler("/settings", [&](IHttpRequest& request,
    const Core::IEntity& entity) {
    return onPutSettings(request, entity);
  });
}

std::unique_ptr<Core::IActionResult>
SettingsController::onGetSettings(IHttpRequest& request) {
  return ObjectResult<Settings>::OK(make_unique<Settings>(
    wifiManager->getDeviceName()
  ));
}

std::unique_ptr<Core::IActionResult>
SettingsController::onPutSettings(
  IHttpRequest& request, const Core::IEntity& entity) {
  auto settings = entity.dynamicCast<Settings>();
  if (settings == nullptr)
    return StatusResult::BadRequest("Type Settings expected.");

  // TODO: Update device settings.
  return ObjectResult<Settings>::OK(make_unique<Settings>(
    wifiManager->getDeviceName()
  ));
}
