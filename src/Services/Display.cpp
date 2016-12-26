#include "Display.hpp"

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

Display::Display(IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue),
  pixels(Core::makeUnique<Adafruit_NeoPixel>(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE)) {

  pixels->begin();
  hasAccessPoint  = false;
  isConnected     = false;
  updateDisplay();

  auto queueController = messageQueue->createController(SenderId);

  colorController = QueueResourceController<Color>::makeUnique(queueController);
  colorController->setOnGetRequestHandler(std::bind(&Display::onGetColor, this));
  colorController->setOnUpdateRequestHandler(std::bind(&Display::onUpdateColor, this, _1));

  auto queueClient = messageQueue->createClient(SenderId);

  connectionClient = QueueResourceClient<Connection>::makeUnique(queueClient);
  connectionClient->setOnGetStatusResponse(std::bind(&Display::onConnectionGetStatusResponse, this, _1));
  connectionClient->setOnGetObjectResponse(std::bind(&Display::onConnectionGetObjectResponse, this, _1));
  connectionClient->setOnCreateNotification(std::bind(&Display::onConnectionCreateNotification, this, _1));
  connectionClient->setOnUpdateNotification(std::bind(&Display::onConnectionUpdateNotification, this, _1));
  connectionClient->setOnDeleteNotification(std::bind(&Display::onConnectionDeleteNotification, this));;

  accessPointClient = QueueResourceClient<AccessPoint>::makeUnique(queueClient);
  accessPointClient->setOnGetStatusResponse(std::bind(&Display::onAccessPointGetStatusResponse, this, _1));
  accessPointClient->setOnGetObjectResponse(std::bind(&Display::onAccessPointGetObjectResponse, this, _1));
  accessPointClient->setOnCreateNotification(std::bind(&Display::onAccessPointCreateNotification, this, _1));
  accessPointClient->setOnDeleteNotification(std::bind(&Display::onAccessPointDeleteNotification, this));;

  connectionClient->getResource();
  accessPointClient->getResource();
}

void
Display::loop() {
  // Perform animation
}

void
Display::colorWipe(uint32_t color) {
  for(uint16_t i = 0; i < pixels->numPixels(); i++) {
    pixels->setPixelColor(i, color);
  }
  pixels->show();
}

void
Display::updateDisplay() {
  if (!isConnected) {
    if (hasAccessPoint) {
      colorWipe(pixels->Color(0, 25, 0));
    } else if (!isConnected) {
      colorWipe(pixels->Color(25, 0, 0));
    }
  } else {
    colorWipe(pixels->Color(r, g, b));
  }
}

Core::ActionResult::Unique
Display::onGetColor() {
  auto color = Color::makeUnique(r, g, b);
  return ObjectResult::makeUnique(StatusCode::OK, std::move(color));
}

Core::StatusResult::Unique
Display::onUpdateColor(const Models::Color& color) {
  r = color.getR(); g = color.getG(); b = color.getB();
  updateDisplay();
  return StatusResult::OK();
}

void
Display::onConnectionGetStatusResponse(const Core::StatusResult& status) {
  isConnected = false;
  updateDisplay();
}

void
Display::onConnectionGetObjectResponse(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
Display::onConnectionCreateNotification(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
Display::onConnectionUpdateNotification(const Connection& connection) {
  isConnected = connection.getIsConnected();
  updateDisplay();
}

void
Display::onConnectionDeleteNotification() {
  isConnected = false;
  updateDisplay();
}

void
Display::onAccessPointGetStatusResponse(const Core::StatusResult& status) {
  hasAccessPoint = false;
  updateDisplay();
}

void
Display::onAccessPointGetObjectResponse(const AccessPoint& accessPoint) {
  hasAccessPoint = true;
  updateDisplay();
}

void
Display::onAccessPointCreateNotification(const AccessPoint& accessPoint) {
  hasAccessPoint = true;
  updateDisplay();
}

void
Display::onAccessPointDeleteNotification() {
  hasAccessPoint = false;
  updateDisplay();
}
