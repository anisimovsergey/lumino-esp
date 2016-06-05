#include "ConnectionController.hpp"

#include "Core/Status.hpp"
#include "Models/Connection.hpp"
#include "Services/IHttpServer.hpp"

using namespace Core;
using namespace Services;
using namespace Models;
using namespace Controllers;

ConnectionController::ConnectionController(
  std::shared_ptr<const IWiFiManager> wifiManager) :
  wifiManager(wifiManager) {
}

void
ConnectionController::onGetConnection(Services::IHttpServer& httpServer) {
  Connection connection(
    wifiManager->getNetwork(),
    wifiManager->isConnected()
  );
  httpServer.sendJson(connection);
}

void
ConnectionController::onPutConnection(Services::IHttpServer& httpServer) {
  std::shared_ptr<IEntity> entity;
  Status status = httpServer.getJson(entity);
  if (status.isOk()) {
    Connection* connection = Connection::dynamicCast(entity.get());
    if (connection != nullptr) {
      httpServer.sendJson(*connection);
    } else {
      httpServer.sendJson(Status::IncorrectObjectType);
    }
  } else {
    httpServer.sendJson(status);
  }
}

void
ConnectionController::registerOn(IHttpServer &httpServer) {
  httpServer.addGetHandler("/connection", [&]() {
    onGetConnection(httpServer);
  });
  httpServer.addPutHandler("/connection", [&]() {
    onPutConnection(httpServer);
  });
}
