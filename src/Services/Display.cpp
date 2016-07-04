#include "Display.hpp"

#include "Core/Memory.hpp"

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN   5    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 12    // The number of NeoPixels connected.
#define PIXEL_TYPE  NEO_GRBW + NEO_KHZ800

using namespace Services;

Display::Display() :
  currentSign(DisplaySign::Undefined),
  pixels(make_unique<Adafruit_NeoPixel>(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE)) {
  pixels->begin();
  colorWipe(pixels->Color(0, 0, 0)); // Initialize all pixels to 'off'
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
Display::colorWipe(uint32_t color) {
  for(uint16_t i = 0; i < pixels->numPixels(); i++) {
    pixels->setPixelColor(i, color);
  }
  pixels->show();
}
