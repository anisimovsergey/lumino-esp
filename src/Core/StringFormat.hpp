// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_STRING_FORMAT_HPP
#define CORE_STRING_FORMAT_HPP

#include "Core/Logger.hpp"

#include <string>
#include <memory>
#include <stdio.h>

namespace Core {

  template<typename ... Args>
  std::string stringFormat(const std::string format, Args ... args) {
    char buffer [0];
    size_t size = snprintf(buffer, 0, format.c_str(), args ...);
    std::unique_ptr<char[]> buf(new char[size + 1]);
    snprintf(buf.get(), size + 1, format.c_str(), args ...);
    return std::string(buf.get(), size);
  }

  inline std::string ipToString(uint32_t ip) {
      uint8_t a = (ip & (0xff << 24)) >> 24;
      uint8_t b = (ip & (0xff << 16)) >> 16;
      uint8_t c = (ip & (0xff << 8)) >> 8;
      uint8_t d = (ip & 0xff);
      return stringFormat("%hu.%hu.%hu.%hu", a, b, c, d);
  }

  inline std::string toString(int val) {
    return stringFormat("%d", val);
  }

  inline std::string toString(unsigned val) {
    return stringFormat("%u", val);
  }

  inline std::string toString(long val) {
    return stringFormat("%ld", val);
  }

  inline std::string toString(unsigned long val) {
    return stringFormat("%lu", val);
  }

  inline std::string toString(long long val) {
    return stringFormat("%lld", val);
  }

  inline std::string toString(unsigned long long val) {
    return stringFormat("%llu", val);
  }

  inline std::string toString(float val) {
    return stringFormat("%f", val);
  }

  inline std::string toString(double val) {
    return stringFormat("%f", val);
  }

  inline std::string toString(long double val) {
    return stringFormat("%Lf", val);
  }
}

#endif /* end of include guard: CORE_STRING_FORMAT_HPP */
