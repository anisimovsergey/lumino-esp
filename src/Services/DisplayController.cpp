#include "DisplayController.hpp"

#include "Core/Memory.hpp"
#include "Models/Connection.hpp"

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN   5    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 12    // The number of NeoPixels connected.
#define PIXEL_TYPE  NEO_GRBW + NEO_KHZ800

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

namespace {
  const char* SenderId = "Display";
}

DisplayController::DisplayController(
  Core::IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue),
  pixels(Core::makeUnique<Adafruit_NeoPixel>(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE)) {

  pixels->begin();
  color           = Color(0,0,0);
  hasAccessPoint  = false;
  isConnected     = false;
  updateDisplay();

  auto queueClient = messageQueue->createClient(SenderId);
  colorClient = QueueResourceClient<Color>::makeUnique(queueClient);
  colorClient->setOnGetObjectResponse(std::bind(&DisplayController::onColorGetObjectResponse, this, _1));
  colorClient->setOnUpdateNotification(std::bind(&DisplayController::onColorUpdateNotification, this, _1));

  connectionClient = QueueResourceClient<Connection>::makeUnique(queueClient);
  connectionClient->setOnGetStatusResponse(std::bind(&DisplayController::onConnectionGetStatusResponse, this, _1));
  connectionClient->setOnGetObjectResponse(std::bind(&DisplayController::onConnectionGetObjectResponse, this, _1));
  connectionClient->setOnCreateNotification(std::bind(&DisplayController::onConnectionCreateNotification, this, _1));
  connectionClient->setOnUpdateNotification(std::bind(&DisplayController::onConnectionUpdateNotification, this, _1));
  connectionClient->setOnDeleteNotification(std::bind(&DisplayController::onConnectionDeleteNotification, this));;

  accessPointClient = QueueResourceClient<AccessPoint>::makeUnique(queueClient);
  accessPointClient->setOnGetStatusResponse(std::bind(&DisplayController::onAccessPointGetStatusResponse, this, _1));
  accessPointClient->setOnGetObjectResponse(std::bind(&DisplayController::onAccessPointGetObjectResponse, this, _1));
  accessPointClient->setOnCreateNotification(std::bind(&DisplayController::onAccessPointCreateNotification, this, _1));
  accessPointClient->setOnDeleteNotification(std::bind(&DisplayController::onAccessPointDeleteNotification, this));;

  connectionClient->getResource();
  accessPointClient->getResource();
}

void
DisplayController::loop() {
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
DisplayController::onConnectionGetStatusResponse(const Core::StatusResult& status) {
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
DisplayController::onAccessPointGetStatusResponse(const Core::StatusResult& status) {
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
