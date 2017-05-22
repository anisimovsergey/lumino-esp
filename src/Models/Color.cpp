#include "Color.hpp"

using namespace Models;

float hue2rgb(float p, float q, float t) {
    if (t < 0) t += 1;
    if (t > 1.0) t -= 1;
    if (t < 1.0/6.0) return p + (q - p) * 6.0 * t;
    if (t < 1.0/2.0) return q;
    if (t < 2.0/3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6;
    return p;
}

Color::Color() : h(.0), s(.0), l(.0) {
}

Color::Color(float h, float s, float l) : h(h), s(s), l(l) {
}

void
Color::toRGB(uint8_t& r, uint8_t& g, uint8_t& b) {
  float rf, gf, bf;

  if (s == 0) {
      rf = gf = bf = l; // achromatic
  } else {
      float q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
      float p = 2.0 * l - q;
      rf = hue2rgb(p, q, h + 1.0 / 3.0);
      gf = hue2rgb(p, q, h);
      bf = hue2rgb(p, q, h - 1.0 / 3.0);
  }

  r = rf * 255;
  g = gf * 255;
  b = bf * 255;
}
