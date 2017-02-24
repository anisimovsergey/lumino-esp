// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_SETTINGS_HPP
#define SERVICES_SETTINGS_HPP

#include "Models/Color.hpp"

#include <Ticker.h>

#include <memory>

namespace Services {

class Settings {
  public:
    std::string     getUniqueName() const;
    std::string     getLocalDomain() const;
};

}

#endif /* end of include guard: SERVICES_SETTINGS_HPP */
