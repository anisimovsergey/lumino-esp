// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_SETTINGS_HPP
#define SERVICES_SETTINGS_HPP

#include "Core/TypeInfo.hpp"

#include <memory>

namespace Services {

class Settings {
  TYPE_PTRS(Settings)
  public:
    std::string getDeviceName()     const;
    int         getWebServerPort()  const;
};

}

#endif /* end of include guard: SERVICES_SETTINGS_HPP */
