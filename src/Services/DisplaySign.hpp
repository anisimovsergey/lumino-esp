// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_DISPLAY_SIGN_HPP
#define SERVICES_DISPLAY_SIGN_HPP

namespace Services {

class DisplaySign {
  public:
    static const DisplaySign Undefined;
    static const DisplaySign Connected;
    static const DisplaySign Disconnected;

    bool operator==(const DisplaySign& other) const {
      return i == other.i;
    }

    bool operator!=(const DisplaySign& other) const {
      return !(*this == other);
    }

  private:
    int i;
    DisplaySign(int i);
};

}

#endif /* end of include guard: SERVICES_DISPLAY_SIGN_HPP */
