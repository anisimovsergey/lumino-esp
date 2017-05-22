// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_DISPLAY_HPP
#define MODELS_DISPLAY_HPP

#include "Core/IEntity.hpp"

namespace Models {

class Color final : public Core::IEntity {
  TYPE_INFO(Color, Core::IEntity, "color")
  public:
    Color();
    Color(float h, float s, float l);

    float      getH() const { return h; };
    float      getS() const { return s; };
    float      getV() const { return v; };

    void       toRGB(uint8_t& r, uint8_t& g, uint8_t& b);

  private:
    float  h;
    float  s;
    float  v;
};

}

#endif /* end of include guard: MODELS_DISPLAY_HPP */
