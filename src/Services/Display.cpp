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
using namespace Messaging;
using namespace std::placeholders;

namespace {
  const char* SenderId = "Display";
}

Display::Display(IMessageQueue::Shared messageQueue) :
  messageQueue(messageQueue),
  pixels(new Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE),
      [](Adafruit_NeoPixel *impl) { delete impl; }) {

  pixels->begin();

  colorWipe(pixels->Color(0, 0, 0));

  auto queueClient = messageQueue->createClient(SenderId, Connection::TypeId());
  queueClient->addOnResponse<Status>("get",
    std::bind(&Display::onConnectionGetStatusResponse, this, _1)
  );
  queueClient->addOnResponse<Connection>("get",
    std::bind(&Display::onConnectionGetResponse, this, _1)
  );
  queueClient->addOnEvent<Connection>("created",
    std::bind(&Display::onConnectionCreatedEvent, this, _1)
  );
  queueClient->addOnEvent<Connection>("updated",
    std::bind(&Display::onConnectionUpdatedEvent, this, _1)
  );
  queueClient->addOnEvent("deleted",
    std::bind(&Display::onConnectionDeletedEvent, this)
  );
  client->sendRequest("get");
}

void
Display::idle() {
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
Display::onConnectionGetStatusResponse(const Core::Status& status) {
  if (status.getStatusCode() == StatusCode::NotFound) {
    colorWipe(pixels->Color(0, 0, 0, 0));
  } else {
    colorWipe(pixels->Color(0, 0, 0, 25));
  }
}

void
Display::onConnectionGetResponse(const Connection& connection) {
  updateConnectionStatus(connection);
}

void
Display::onConnectionCreatedEvent(const Connection& connection) {
  updateConnectionStatus(connection);
}

void
Display::onConnectionUpdatedEvent(const Connection& connection) {
  updateConnectionStatus(connection);
}

void
Display::onConnectionDeletedEvent() {
  colorWipe(pixels->Color(0, 0, 0, 0));
}
