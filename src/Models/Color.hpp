// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_DISPLAY_HPP
#define MODELS_DISPLAY_HPP

#include "WString.h"
#include "Core/IEntity.hpp"

namespace Models {

class Color : public Core::IEntity {
  TYPE_INFO(Color, Core::IEntity, "color")
  public:
    Color(uint8_t r, uint8_t g, uint8_t b);

    uint8_t      getR() const { return r; };
    uint8_t      getG() const { return g; };
    uint8_t      getB() const { return b; };

  private:
    uint8_t  r;
    uint8_t  g;
    uint8_t  b;
};

}

#endif /* end of include guard: MODELS_DISPLAY_HPP */
