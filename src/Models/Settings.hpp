// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_SETTINGS_HPP
#define MODELS_SETTINGS_HPP

#include "Core/IEntity.hpp"

namespace Models {

class Settings final : public Core::IEntity {
  TYPE_INFO(Settings, Core::IEntity, "settings")
  public:
    Settings(std::string uniqueName, std::string deviceName);

    std::string getUniqueName() const { return uniqueName; }
    std::string getDeviceName() const { return deviceName; };

  private:
    std::string uniqueName;
    std::string deviceName;
};

}

#endif /* end of include guard: MODELS_SETTINGS_HPP */
