#include "Connection.hpp"

using namespace Models;

Connection::Connection(
  std::string networkSsid,
  bool isConnected) :
  networkSsid(networkSsid),
  isConnected(isConnected) {
}

Connection::Connection(
  std::string networkSsid,
  std::string networkPassword) :
  networkSsid(networkSsid),
  networkPassword(networkPassword) {
}
