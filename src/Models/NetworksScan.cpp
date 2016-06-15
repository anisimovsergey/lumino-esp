#include "NetworksScan.hpp"

using namespace Core;
using namespace Models;

NetworksScan::NetworksScan(String status, List<Network> networks) :
  status(status), networks(std::move(networks)) {

}
