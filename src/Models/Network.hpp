#ifndef NETWORK_H
#define NETWORK_H

#include <WString.h>

class Network {
public:
  Network(String ssid, int rssi, int encryptionType);

  String  getSsid() const { return ssid; };
  int     getRssi() const { return rssi; };
  int     getEncryptionType() const { return encryptionType; };

private:
  String  ssid;
  int     rssi;
  int     encryptionType;
};

#endif /* end of include guard: NETWORK_H */
