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

std::unique_ptr<IActionResult>
ConnectionController::onGetConnection(
  IHttpRequest& request) {

  if (!wifiManager->hasConnection())
    return StatusResult::NotFound("Connection doesn't exist.");

  return ObjectResult::OK(
    make_unique<Connection>(
      wifiManager->getNetwork(),
      wifiManager->isConnected()
    ));
}

std::unique_ptr<IActionResult>
ConnectionController::onPostConnection(
  IHttpRequest& request,
  const IEntity& entity) {

  if (wifiManager->hasConnection())
    return StatusResult::Conflict("Connection already exists.");

  auto connection = entity.dynamicCast<Connection>();
  if (connection == nullptr)
    return StatusResult::BadRequest("Type Connection expected.");

  auto result = wifiManager->connect(
    connection->getNetworkSsid(),
    connection->getNetworkPassword());
  if (!result->isOk())
    return StatusResult::InternalServerError("Unable to create a connection",
      std::move(result));

  return RedirectResult::ToRoute("/connection");
}

std::unique_ptr<IActionResult>
ConnectionController::onDeleteConnection(
  IHttpRequest& request) {

  if (!wifiManager->hasConnection())
    return StatusResult::NotFound("Connection doesn't exist.");

  return wifiManager->disconnect();
}
