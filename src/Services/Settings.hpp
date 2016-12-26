// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_SETTINGS_HPP
#define SERVICES_SETTINGS_HPP

#include "Core/TypeInfo.hpp"
#include "Models/Color.hpp"

#include <memory>

namespace Services {

class Settings {
  TYPE_PTRS(Settings)
  public:
    Settings();

    std::string     getDeviceName()     const;
    std::string     getLocalDomain()    const;
    int             getWebServerPort()  const;

    Models::Color   getColor() const;
    void            setColor(const Models::Color& color);

  private:
    Models::Color   color;

    void            readSettings();
    void            writeSettings();
};

}

#endif /* end of include guard: SERVICES_SETTINGS_HPP */
