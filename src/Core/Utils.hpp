// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_UTILS_HPP
#define CORE_UTILS_HPP

#include <WString.h>
#include <IPAddress.h>

namespace Core {

class Utils {
  public:
    static String toStringIp(IPAddress ip) {
      String res = "";
      for (int i = 0; i < 3; i++) {
        res += String((ip >> (8 * i)) & 0xFF) + ".";
      }
      res += String(((ip >> 8 * 3)) & 0xFF);
      return res;
    }
};

}

#endif /* end of include guard: CORE_UTILS_HPP */
