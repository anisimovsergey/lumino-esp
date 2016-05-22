#ifndef SETTINGS_H
#define SETTINGS_H

#include <WString.h>

class Settings {
public:
  Settings(String deviceName, String networkSsid, String networkPassword);

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

#endif /* end of include guard: SETTINGS_H */
