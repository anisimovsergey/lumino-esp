#include "Connection.hpp"

using namespace Models;

Connection::Connection(
  std::string ssid,
  bool        isConnected,
  bool        isProtected,
  int         rssi,
  uint32_t    localIP,
  uint32_t    subnetMask,
  uint32_t    gatewayIP,
  uint32_t    dnsIP) :
  ssid(ssid),
  isConnected(isConnected),
  isProtected(isProtected),
  rssi(rssi),
  localIP(localIP),
  subnetMask(subnetMask),
  gatewayIP(gatewayIP),
  dnsIP(dnsIP) {
}

Connection::Connection(
  std::string ssid,
  std::string password) :
  ssid(ssid),
  password(password) {
}
