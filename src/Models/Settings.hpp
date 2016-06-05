// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_SETTINGS_H
#define MODELS_SETTINGS_H

#include "Core/Entity.hpp"

namespace Models {

class Settings : public Core::Entity<Settings> {
  public:
    Settings(
      String  deviceName
    );

    static String  getStaticTypeId() { return "settings"; }

    String      getDeviceName() const { return deviceName; };

  private:
    String  deviceName;
};

}

#endif /* end of include guard: MODELS_SETTINGS_H */
