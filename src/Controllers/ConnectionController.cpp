#include "ConnectionController.hpp"

#include "Models/Connection.hpp"
#include "Services/IHttpServer.hpp"

using namespace Core;
using namespace Services;
using namespace Models;
using namespace Controllers;

ConnectionController::ConnectionController(
  std::shared_ptr<IWiFiManager> wifiManager) :
  wifiManager(wifiManager) {
}

void
ConnectionController::registerOn(IHttpServer &httpServer) {
  httpServer.addGetHandler("/connection", [&](IHttpRequest& request) {
    return onGetConnection(request);
  });
  httpServer.addPostHandler("/connection", [&](IHttpRequest& request,
    const Core::IEntity& entity) {
    return onPostConnection(request, entity);
  });
  httpServer.addDeleteHandler("/connection", [&](IHttpRequest& request) {
    return onDeleteConnection(request);
  });
}

std::shared_ptr<IActionResult>
ConnectionController::onGetConnection(IHttpRequest& request) {
  if (!wifiManager->hasConnection())
    return StatusResult::NotFound("Connection doesn't exist.");

  return ObjectResult::OK(
    std::shared_ptr<IEntity>(new Connection(
      wifiManager->getNetwork(),
      wifiManager->isConnected()
    )));
}

std::shared_ptr<IActionResult>
ConnectionController::onPostConnection(IHttpRequest& request, const IEntity& entity) {
  if (wifiManager->hasConnection())
    return StatusResult::Conflict("Connection already exists.");

  auto connection = entity.dynamicCast<Connection>();
  if (connection == nullptr)
    return StatusResult::BadRequest("Type Connection expected.");

  auto actionResult = wifiManager->connect(
    connection->getNetworkSsid(),
    connection->getNetworkPassword());
  if (!actionResult->isOk())
    return actionResult;

  return RedirectResult::ToRoute("/connection");
}

std::shared_ptr<IActionResult>
ConnectionController::onDeleteConnection(IHttpRequest& request) {
  if (!wifiManager->hasConnection())
    StatusResult::NotFound("Connection doesn't exist.");

  return wifiManager->disconnect();
}
