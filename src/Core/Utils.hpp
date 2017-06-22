// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_UTILS_HPP
#define CORE_UTILS_HPP

#include "Core/Format.hpp"

namespace Core {

  std::string
  inline ipToStr(uint32_t ip) {
    uint8_t a = static_cast<uint8_t>((ip & (0xff << 24)) >> 24);
    uint8_t b = static_cast<uint8_t>((ip & (0xff << 16)) >> 16);
    uint8_t c = static_cast<uint8_t>((ip & (0xff << 8)) >> 8);
    uint8_t d = static_cast<uint8_t>(ip & 0xff);
    return stringFormat("%hu.%hu.%hu.%hu", d, c, b, a);
  }

}

#endif /* end of include guard: CORE_UTILS_HPP */
