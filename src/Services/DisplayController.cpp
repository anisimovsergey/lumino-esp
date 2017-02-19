#include "DisplayController.hpp"

#include "Core/Memory.hpp"
#include "Models/Connection.hpp"

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN   5    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 12    // The number of NeoPixels connected.
#define PIXEL_TYPE  NEO_GRBW + NEO_KHZ800

using namespace Core;
using namespace Models;
using namespace Messaging;
using namespace Services;

namespace {
  const char* SenderId = "Display";
}

DisplayController::DisplayController(
  IMessageQueue& messageQueue) :
  messageQueue(messageQueue),
  pixels(new Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE),
  [](Adafruit_NeoPixel *impl) { delete impl; }) {

  pixels->begin();
  color           = Color(0,0,0);
  hasAccessPoint  = false;
  isConnected     = false;
  updateDisplay();

  colorClient = messageQueue.createClient(SenderId, Color::TypeId());
  colorClient->addOnResponse("get", [=](const Models::Color& color) {
    onColorGetObjectResponse(color);
  });
  colorClient->addOnEvent("updated", [=](const Models::Color& color) {
    onColorUpdateNotification(color);
  });

  connectionClient = messageQueue.createClient(SenderId, Connection::TypeId());
  connectionClient->addOnResponse("get", [=](const Core::Status& status) {
    onConnectionGetStatusResponse(status);
  });
  connectionClient->addOnResponse("get", [=](const Models::Connection& connection) {
    onConnectionGetObjectResponse(connection);
  });
  connectionClient->addOnEvent("created", [=](const Models::Connection& connection) {
    onConnectionCreateNotification(connection);
  });
  connectionClient->addOnEvent("updated", [=](const Models::Connection& connection) {
    onConnectionUpdateNotification(connection);
  });
  connectionClient->addOnEvent("deleted", [=]() {
    onConnectionDeleteNotification();
  });

  accessPointClient = messageQueue.createClient(SenderId, AccessPoint::TypeId());
  accessPointClient->addOnResponse("get", [=](const Core::Status& status) {
    onAccessPointGetStatusResponse(status);
  });
  accessPointClient->addOnResponse("get", [=](const Models::AccessPoint& accessPoint) {
    onAccessPointGetObjectResponse(accessPoint);
  });
  accessPointClient->addOnEvent("created", [=](const Models::AccessPoint& accessPoint) {
    onAccessPointCreateNotification(accessPoint);
  });
  accessPointClient->addOnEvent("deleted", [=]() {
    onAccessPointDeleteNotification();
  });

  connectionClient->sendRequest("get");
  accessPointClient->sendRequest("get");
}

void
DisplayController::idle() {
}

void
DisplayController::colorWipe(uint32_t color) {
  for(uint16_t i = 0; i < pixels->numPixels(); i++) {
    pixels->setPixelColor(i, color);
  }
  pixels->show();
}

void
DisplayController::updateDisplay() {
  if (!isConnected) {
    if (hasAccessPoint) {
      colorWipe(pixels->Color(0, 25, 0));
    } else if (!isConnected) {
      colorWipe(pixels->Color(25, 0, 0));
    }
  } else {
    colorWipe(pixels->Color(color.getR(), color.getG(), color.getB()));
  }
}

void
DisplayController::onColorGetObjectResponse(const Color& color) {
  this->color = color;
  updateDisplay();
}

void
DisplayController::onColorUpdateNotification(const Color& color) {
  this->color = color;
  updateDisplay();
}

void
DisplayController::onConnectionGetStatusResponse(const Core::Status& status) {
  isConnected = false;
  updateDisplay();
}

void
DisplayController::onConnectionGetObjectResponse(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
DisplayController::onConnectionCreateNotification(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
DisplayController::onConnectionUpdateNotification(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
DisplayController::onConnectionDeleteNotification() {
  isConnected = false;
  updateDisplay();
}

void
DisplayController::onAccessPointGetStatusResponse(const Core::Status& status) {
  hasAccessPoint = false;
  updateDisplay();
}

void
DisplayController::onAccessPointGetObjectResponse(const AccessPoint& accessPoint) {
  hasAccessPoint = true;
  updateDisplay();
}

void
DisplayController::onAccessPointCreateNotification(const AccessPoint& accessPoint) {
  hasAccessPoint = true;
  updateDisplay();
}

void
DisplayController::onAccessPointDeleteNotification() {
  hasAccessPoint = false;
  updateDisplay();
}
