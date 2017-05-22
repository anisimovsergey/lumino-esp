#include "Color.hpp"

#include <math.h>

using namespace Models;

Color::Color() : h(.0), s(.0), v(.0) {
}

Color::Color(float h, float s, float v) : h(h), s(s), v(v) {
}

void
Color::toRGB(uint8_t& r, uint8_t& g, uint8_t& b) {
   float rx = .0, gx = .0, bx = .0;

   int i = int(floor(h * 6.0));
   float f = h * 6.0 - i;
   float p = v * (1.0 - s);
   float q = v * (1.0 - f * s);
   float t = v * (1.0 - (1.0 - f) * s);

   switch(i % 6){
       case 0: rx = v, gx = t, bx = p; break;
       case 1: rx = q, gx = v, bx = p; break;
       case 2: rx = p, gx = v, bx = t; break;
       case 3: rx = p, gx = q, bx = v; break;
       case 4: rx = t, gx = p, bx = v; break;
       case 5: rx = v, gx = p, bx = q; break;
   }

   r = rx * 255;
   g = gx * 255;
   b = bx * 255;
}
