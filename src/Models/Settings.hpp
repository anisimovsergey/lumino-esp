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
    Settings();

    Settings(
      String  deviceName,
      String  networkSsid,
      String  networkPassword,
      bool    isConnected
    );

    static String  getStaticTypeId() { return "settings"; }

    String  getDeviceName() const { return deviceName; };
    String  getNetworkSsid() const { return networkSsid; };
    String  getNetworkPassword() const { return networkPassword; };
    bool    getIsConnected() const { return isConnected; };

  private:
    String  deviceName;
    String  networkSsid;
    String  networkPassword;
    bool    isConnected;
};

}

#endif /* end of include guard: MODELS_SETTINGS_H */
