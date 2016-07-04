// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_DISPLAY_HPP
#define SERVICES_DISPLAY_HPP

#include "IDisplay.hpp"

#include <memory>

class Adafruit_NeoPixel;

namespace Services {

class Display : public IDisplay {
  public:
    Display();

    virtual void showSigh(const DisplaySign& sign) override;

  private:
    DisplaySign currentSign;
    std::unique_ptr<Adafruit_NeoPixel> pixels;
    void colorWipe(uint32_t color);
};

}

#endif /* end of include guard: SERVICES_DISPLAY_HPP */
