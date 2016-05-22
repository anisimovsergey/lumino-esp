#ifndef NETWORK_H
#define NETWORK_H

#include <WString.h>

class Network {
public:
  Network(String ssid, float rssi, int encryptionType);

  String  getSsid() { return ssid; };
  float   getRssi() { return rssi;};
  int     getEncryptionType() { return encryptionType; };

private:
  String  ssid;
  float   rssi;
  int     encryptionType;
};

#endif /* end of include guard: NETWORK_H */
