// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_DISPLAY_HPP
#define SERVICES_I_DISPLAY_HPP

#include "DisplaySign.hpp"

namespace Services {

class IDisplay {
  public:
    virtual ~IDisplay();

    virtual void showSigh(const DisplaySign& sign) = 0;
};

}

#endif /* end of include guard: SERVICES_I_DISPLAY_HPP */
