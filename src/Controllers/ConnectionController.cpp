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

void
ConnectionController::onGetConnection(IHttpRequest& request) {
  Status status;
  if (!wifiManager->hasConnection()) {
    Connection connection(
      wifiManager->getNetwork(),
      wifiManager->isConnected()
    );
    request.sendJson(connection);
  } else {
    status = Status::ResourceNotFound;
    request.sendJson(status);
  }
}

void
ConnectionController::onPostConnection(IHttpRequest& request) {
  std::shared_ptr<IEntity> entity;
  Status status = request.getJson(entity);
  if (status.isOk()) {
    Connection* connection = Connection::dynamicCast(entity.get());
    if (connection != nullptr) {
      status = wifiManager->connect(
        connection->getNetworkSsid(),
        connection->getNetworkPassword());
      if (status.isOk()) {
        status = Status::ResourceCreated;
        request.addHeader("Location", "/connection");
      }
      request.sendJson(status);
    } else {
      request.sendJson(Status::IncorrectObjectType);
    }
  } else {
    request.sendJson(status);
  }
}

void
ConnectionController::onDeleteConnection(IHttpRequest& request) {

  Status status;
  if (wifiManager->hasConnection()) {
    status = wifiManager->disconnect();
  } else {
    status = Status::ResourceNotFound;
  }
  request.sendJson(status);
}
