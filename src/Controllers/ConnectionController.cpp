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

std::shared_ptr<ActionResult>
ConnectionController::onGetConnection(IHttpRequest& request) {
  if (!wifiManager->hasConnection())
    return ActionResult::ResourceNotFound();

  return ActionResult::Success(
    std::shared_ptr<IEntity>(new Connection(
      wifiManager->getNetwork(),
      wifiManager->isConnected()
    )));
}

std::shared_ptr<ActionResult>
ConnectionController::onPostConnection(IHttpRequest& request, const IEntity& entity) {
  if (wifiManager->hasConnection())
    return ActionResult::Conflict();

  auto connection = Connection::dynamicCast(&entity);
  if (connection == nullptr)
    return ActionResult::IncorrectObjectType();

  auto actionResult = wifiManager->connect(
    connection->getNetworkSsid(),
    connection->getNetworkPassword());
  if (!actionResult->isOk())
    return actionResult;

  return ActionResult::RedirectTo("/connection");
}

std::shared_ptr<ActionResult>
ConnectionController::onDeleteConnection(IHttpRequest& request) {
  if (!wifiManager->hasConnection())
    ActionResult::ResourceNotFound();

  return wifiManager->disconnect();
}
