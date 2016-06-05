#include "Connection.hpp"

using namespace Models;

Connection::Connection(
  String networkSsid,
  bool isConnected) :
  networkSsid(networkSsid),
  isConnected(isConnected) {
}

Connection::Connection(
  String networkSsid,
  String networkPassword,
  bool isConnected) :
  networkSsid(networkSsid),
  networkPassword(networkPassword),
  isConnected(isConnected) {
}
