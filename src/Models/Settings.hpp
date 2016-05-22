#ifndef SETTINGS_H
#define SETTINGS_H

#include <WString.h>

class Settings {
public:
  Settings(String deviceName, String networkSsid, String networkPassword);

  String  getDeviceName() { return deviceName; };
  String  getNetworkSsid() { return networkSsid; };
  String  getNetworkPassword() { return networkPassword; };

private:
  String  deviceName;
  String  networkSsid;
  String  networkPassword;
};

#endif /* end of include guard: SETTINGS_H */
