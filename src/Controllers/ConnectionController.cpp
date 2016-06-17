#include "ConnectionController.hpp"

#include "Core/Status.hpp"
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
    onGetConnection(request);
  });
  httpServer.addPostHandler("/connection", [&](IHttpRequest& request) {
    onPostConnection(request);
  });
  httpServer.addDeleteHandler("/connection", [&](IHttpRequest& request) {
    onDeleteConnection(request);
  });
}

IHttpResponse
ConnectionController::onGetConnection(IHttpRequest& request) {
  if (!wifiManager->hasConnection())
    return Status::ResourceNotFound;

  return Connection(
    wifiManager->getNetwork(),
    wifiManager->isConnected()
  );
}

IHttpResponse
ConnectionController::onPostConnection(IHttpRequest& request) {
  if (wifiManager->hasConnection())
    return Status::Conflict;

  std::shared_ptr<IEntity> entity;
  Status status = request.getJson(entity);
  if (!status.isOk())
    return status;

  Connection* connection = Connection::dynamicCast(entity.get());
  if (connection == nullptr)
    return Status::IncorrectObjectType;

  status = wifiManager->connect(
    connection->getNetworkSsid(),
    connection->getNetworkPassword());
  if (!status.isOk())
    return Response::status(status);

  return Response::resourceCreated("/connection");
}

IHttpResponse
ConnectionController::onDeleteConnection(IHttpRequest& request) {
  Status status;
  if (wifiManager->hasConnection()) {
    status = wifiManager->disconnect();
  } else {
    status = Status::ResourceNotFound;
  }
  return Response::Status(status);
}
