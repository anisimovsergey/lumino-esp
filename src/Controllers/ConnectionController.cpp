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
ConnectionController::onGetConnection(Services::IHttpServer& httpServer) {

  Status status;
  if (!wifiManager->hasConnection()) {
    Connection connection(
      wifiManager->getNetwork(),
      wifiManager->isConnected()
    );
    httpServer.sendJson(connection);
  } else {
    status = Status::ResourceNotFound;
    httpServer.sendJson(status);
  }
}

void
ConnectionController::onPostConnection(Services::IHttpServer& httpServer) {
  std::shared_ptr<IEntity> entity;
  Status status = httpServer.getJson(entity);
  if (status.isOk()) {
    Connection* connection = Connection::dynamicCast(entity.get());
    if (connection != nullptr) {
      status = wifiManager->connect(
        connection->getNetworkSsid(),
        connection->getNetworkPassword());
      if (status.isOk()) {
        status = Status::ResourceCreated;
        httpServer.setLocation("/connection");
      }
      httpServer.sendJson(status);
    } else {
      httpServer.sendJson(Status::IncorrectObjectType);
    }
  } else {
    httpServer.sendJson(status);
  }
}

void
ConnectionController::onDeleteConnection(Services::IHttpServer& httpServer) {

  Status status;
  if (wifiManager->hasConnection()) {
    status = wifiManager->disconnect();
  } else {
    status = Status::ResourceNotFound;
  }
  httpServer.sendJson(status);
}

void
ConnectionController::registerOn(IHttpServer &httpServer) {
  httpServer.addGetHandler("/connection", [&]() {
    onGetConnection(httpServer);
  });
  httpServer.addPostHandler("/connection", [&]() {
    onPostConnection(httpServer);
  });
  httpServer.addDeleteHandler("/connection", [&]() {
    onDeleteConnection(httpServer);
  });
}
