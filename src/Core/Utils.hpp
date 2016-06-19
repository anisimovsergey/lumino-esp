// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#include <WString.h>
#include <IPAddress.h>

namespace Core {

class Utils {
  public:

    static bool isIp(String str) {
      for (size_t i = 0; i < str.length(); i++) {
        int c = str.charAt(i);
        if (c != '.' && (c < '0' || c > '9')) {
          return false;
        }
      }
      return true;
    }

    static String toStringIp(IPAddress ip) {
      String res = "";
      for (int i = 0; i < 3; i++) {
        res += String((ip >> (8 * i)) & 0xFF) + ".";
      }
      res += String(((ip >> 8 * 3)) & 0xFF);
      return res;
    }

  private:
    Utils() {};
};

}

#endif /* end of include guard: CORE_UTILS_H */
