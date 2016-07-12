#include "ConnectionController.hpp"

#include "Models/Connection.hpp"
#include "Services/IHttpServer.hpp"

using namespace Core;
using namespace Services;
using namespace Models;
using namespace Controllers;

static const String ConnectionUrl = "/connection";

ConnectionController::ConnectionController(
  std::shared_ptr<IWiFiManager> wifiManager) :
  wifiManager(wifiManager) {
}

void
ConnectionController::registerOn(IHttpServer& httpServer) {
  httpServer.addGetHandler(ConnectionUrl, [&](IHttpRequest& request) {
    return onGetConnection(request);
  });
  httpServer.addPostHandler(ConnectionUrl, [&](IHttpRequest& request,
    const Core::IEntity& entity) {
    return onPostConnection(request, entity);
  });
  httpServer.addDeleteHandler(ConnectionUrl, [&](IHttpRequest& request) {
    return onDeleteConnection(request);
  });
}

std::unique_ptr<IActionResult>
ConnectionController::onGetConnection(
  IHttpRequest& request) {

  auto message = request.createMessage(Message::GetConnection);
  return messageQueue->addMessage(message);
}

std::unique_ptr<IActionResult>
ConnectionController::onPostConnection(
  IHttpRequest& request,
  const IEntity& entity) {

  auto connection = entity.dynamicCast<Connection>();
    if (connection == nullptr)
      return StatusResult::BadRequest("Type Connection expected.");

  auto message = request.createMessage(
    Message::CreateConnection(connection, ConnectionUrl));
  return messageQueue->addMessage(message);
}

std::unique_ptr<IActionResult>
ConnectionController::onDeleteConnection(
  IHttpRequest& request) {

  auto message = request.createMessage(Message::DeleteConnection);
  return messageQueue->addMessage(message);
}
