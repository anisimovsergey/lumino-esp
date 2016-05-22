#ifndef NETWORK_H
#define NETWORK_H

#include <WString.h>

class Network {
public:
  Network(String ssid, float rssi, int encryptionType);

  String  getSsid() const { return ssid; };
  float   getRssi() const { return rssi; };
  int     getEncryptionType() const { return encryptionType; };

private:
  String  ssid;
  float   rssi;
  int     encryptionType;
};

#endif /* end of include guard: NETWORK_H */
