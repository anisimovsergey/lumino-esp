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
  const char* ConnectionResource = "/connection";
}

Display::Display(std::shared_ptr<Core::IMessageQueue> messageQueue) :
  messageQueue(messageQueue),
  currentSign(DisplaySign::Undefined),
  pixels(make_unique<Adafruit_NeoPixel>(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE)) {
  pixels->begin();
  colorWipe(pixels->Color(0, 0, 0)); // Initialize all pixels to 'off'

  auto messageSender = std::make_shared<MessageSender>(SenderId,
    std::bind(&Display::onResponse, this, _1),
    std::bind(&Display::onNotification, this, _1));
  messageQueue->addMessageSender(messageSender);

  auto reqiest = std::make_shared<Request>(ActionType::Get, ConnectionResource);
  messageQueue->send(SenderId, reqiest);
}

void
Display::showSigh(const DisplaySign& sign) {
  if (sign == currentSign)
    return;

  if (sign == DisplaySign::Connected)
    colorWipe(pixels->Color(0, 0, 0, 0));
  if (sign == DisplaySign::Disconnected)
    colorWipe(pixels->Color(25, 0, 0, 0));

  currentSign = sign;
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
Display::onResponse(std::shared_ptr<Core::Response> response) {

}

void
Display::onNotification(std::shared_ptr<Core::Notification> notification) {
  if (notification->getActionType() == ActionType::Get &&
    notification->getResource() == ConnectionResource) {
    auto objectResult = ObjectResult::cast(&notification->getResult());
    if (objectResult) {
      auto connection = Connection::cast(&objectResult->getObject());
      if (connection) {
        if (connection->getIsConnected())
          colorWipe(pixels->Color(0, 25, 0, 0));
        else
          colorWipe(pixels->Color(25, 0, 0, 0));
      }
    } 
    auto statusResult = StatusResult::cast(&notification->getResult());
    if (statusResult) {
      if (statusResult->getStatusCode() == StatusCode::NotFound) {
        colorWipe(pixels->Color(0, 0, 0, 0));
      }
    }
    auto messageListener = std::make_shared<MessageListener>(
      std::bind(&Display::onBroadcast, this, _1));
    messageQueue->addMessageListener(messageListener);
  }
}

void
Display::onBroadcast(Notification::Shared notification) {
  if (notification->getActionType() == ActionType::Update &&
      notification->getResource() == ConnectionResource) {
    auto objectResult = ObjectResult::cast(&notification->getResult());
    if (objectResult) {
      auto connection = Connection::cast(&objectResult->getObject());
      if (connection) {
        if (connection->getIsConnected())
          colorWipe(pixels->Color(0, 25, 0, 0));
        else
          colorWipe(pixels->Color(25, 0, 0, 0));
      }
    }
  } else if (notification->getActionType() == ActionType::Create &&
             notification->getResource() == ConnectionResource) {
     auto objectResult = ObjectResult::cast(&notification->getResult());
     if (objectResult) {
       auto connection = Connection::cast(&objectResult->getObject());
       if (connection) {
         if (connection->getIsConnected())
           colorWipe(pixels->Color(0, 25, 0, 0));
         else
           colorWipe(pixels->Color(25, 0, 0, 0));
       }
     }
  } else if (notification->getActionType() == ActionType::Delete &&
             notification->getResource() == ConnectionResource) {
     auto statusResult = StatusResult::cast(&notification->getResult());
     if (statusResult) {
       if (statusResult->getStatusCode() == StatusCode::NoContent) {
         colorWipe(pixels->Color(0, 0, 0, 0));
       }
     }
  }
}
