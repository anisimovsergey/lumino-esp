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

Display::Display(std::shared_ptr<IMessageQueue> messageQueue) :
  messageQueue(messageQueue),
  pixels(makeUnique<Adafruit_NeoPixel>(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE)) {

  pixels->begin();

  colorWipe(pixels->Color(0, 0, 0));

  auto queueClient = messageQueue->createClient(SenderId);
  client = QueueResourceClient<Connection>::makeUnique(queueClient);

  client->setOnGetStatusResponse(
    std::bind(&Display::onConnectionGetStatusResponse, this, _1));
  client->setOnGetObjectResponse(
    std::bind(&Display::onConnectionGetObjectResponse, this, _1));
  client->setOnCreateNotification(
    std::bind(&Display::onConnectionCreateNotification, this, _1));
  client->setOnUpdateNotification(
    std::bind(&Display::onConnectionUpdateNotification, this, _1));
  client->setOnDeleteNotification(
    std::bind(&Display::onConnectionDeleteNotification, this));;

  client->getResource();
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
Display::updateConnectionStatus(const Connection& connection) {
  if (connection.getIsConnected())
    colorWipe(pixels->Color(0, 25, 0, 0));
  else
    colorWipe(pixels->Color(25, 0, 0, 0));
}

void
Display::onConnectionGetStatusResponse(const Core::StatusResult& status) {
  if (status.getStatusCode() == StatusCode::NotFound) {
    colorWipe(pixels->Color(0, 0, 0, 0));
  } else {
    colorWipe(pixels->Color(0, 0, 0, 25));
  }
}

void
Display::onConnectionGetObjectResponse(const Connection& connection) {
  updateConnectionStatus(connection);
}

void
Display::onConnectionCreateNotification(const Connection& connection) {
  updateConnectionStatus(connection);
}

void
Display::onConnectionUpdateNotification(const Connection& connection) {
  updateConnectionStatus(connection);
}

void
Display::onConnectionDeleteNotification() {
  colorWipe(pixels->Color(0, 0, 0, 0));
}
