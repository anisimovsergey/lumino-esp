// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_SETTINGS_H
#define MODELS_SETTINGS_H

#include "Core/ISerializable.hpp"

namespace Models {

class Settings : public Core::ISerializable {
  public:
    Settings(String deviceName, String networkSsid, String networkPassword);

    String getTypeId() const override { return "settings"; }

    String  getDeviceName() const { return deviceName; };
    String  getNetworkSsid() const { return networkSsid; };
    String  getNetworkPassword() const { return networkPassword; };

    bool    getIsConnected() const { return isConnected; };
    void    setIsConnected(bool value) { isConnected = value; };

  private:
    String  deviceName;
    String  networkSsid;
    String  networkPassword;
    bool    isConnected;
};

}

#endif /* end of include guard: MODELS_SETTINGS_H */
