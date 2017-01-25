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

using namespace std::placeholders;

namespace {
  const char* SenderId = "Display";
}

DisplayController::DisplayController(
  IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue),
  pixels(new Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE),
  [](Adafruit_NeoPixel *impl) { delete impl; }) {

  pixels->begin();
  color           = Color(0,0,0);
  hasAccessPoint  = false;
  isConnected     = false;
  updateDisplay();

  colorClient = messageQueue->createClient(SenderId, Color::TypeId());
  colorClient->addOnResponse<Color>("get", std::bind(&DisplayController::onColorGetObjectResponse, this, _1));
  colorClient->addOnEvent<Color>("updated", std::bind(&DisplayController::onColorUpdateNotification, this, _1));

  connectionClient = messageQueue->createClient(SenderId, Connection::TypeId());
  connectionClient->addOnResponse<Status>("get", std::bind(&DisplayController::onConnectionGetStatusResponse, this, _1));
  connectionClient->addOnResponse<Connection>("get", std::bind(&DisplayController::onConnectionGetObjectResponse, this, _1));
  connectionClient->addOnEvent<Connection>("created", std::bind(&DisplayController::onConnectionCreateNotification, this, _1));
  connectionClient->addOnEvent<Connection>("updated", std::bind(&DisplayController::onConnectionUpdateNotification, this, _1));
  connectionClient->addOnEvent("deleted", std::bind(&DisplayController::onConnectionDeleteNotification, this));;

  accessPointClient = messageQueue->createClient(SenderId, AccessPoint::TypeId());
  accessPointClient->addOnResponse<Status>("get", std::bind(&DisplayController::onAccessPointGetStatusResponse, this, _1));
  accessPointClient->addOnResponse<AccessPoint>("get", std::bind(&DisplayController::onAccessPointGetObjectResponse, this, _1));
  accessPointClient->addOnEvent<AccessPoint>("created", std::bind(&DisplayController::onAccessPointCreateNotification, this, _1));
  accessPointClient->addOnEvent("deleted", std::bind(&DisplayController::onAccessPointDeleteNotification, this));;

  connectionClient->sendRequest("get");
  accessPointClient->sendRequest("get");
}

void
DisplayController::idle() {
  // Perform animation
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
