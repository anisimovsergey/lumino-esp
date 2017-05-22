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
  color           = Color();
  hasAccessPoint  = false;
  isConnected     = false;
  updateDisplay();

  colorClient = messageQueue.createClient(SenderId, Color::TypeId());
  colorClient->addOnEvent(EventType::Created, [=](const Models::Color& color) {
    onColorCreated(color);
  });
  colorClient->addOnEvent(EventType::Updated, [=](const Models::Color& color) {
    onColorUpdated(color);
  });

  connectionClient = messageQueue.createClient(SenderId, Connection::TypeId());
  connectionClient->addOnEvent(EventType::Created, [=](const Models::Connection& connection) {
    onConnectionCreated(connection);
  });
  connectionClient->addOnEvent(EventType::Updated, [=](const Models::Connection& connection) {
    onConnectionUpdated(connection);
  });
  connectionClient->addOnEvent(EventType::Deleted, [=]() {
    onConnectionDeleted();
  });

  accessPointClient = messageQueue.createClient(SenderId, AccessPoint::TypeId());
  accessPointClient->addOnEvent(EventType::Created, [=](const Models::AccessPoint& accessPoint) {
    onAccessPointCreated(accessPoint);
  });
  accessPointClient->addOnEvent(EventType::Deleted, [=]() {
    onAccessPointDeleted();
  });
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
    } else {
      colorWipe(pixels->Color(25, 0, 0));
    }
  } else {
    uint8_t r, g, b;
    color.toRGB(r, g, b);
    colorWipe(pixels->Color(r, g, b));
  }
}

void
DisplayController::onColorCreated(const Color& color) {
  this->color = color;
  updateDisplay();
}

void
DisplayController::onColorUpdated(const Color& color) {
  this->color = color;
  updateDisplay();
}

void
DisplayController::onConnectionCreated(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
DisplayController::onConnectionUpdated(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
DisplayController::onConnectionDeleted() {
  isConnected = false;
  updateDisplay();
}

void
DisplayController::onAccessPointCreated(const AccessPoint& accessPoint) {
  hasAccessPoint = true;
  updateDisplay();
}

void
DisplayController::onAccessPointDeleted() {
  hasAccessPoint = false;
  updateDisplay();
}
