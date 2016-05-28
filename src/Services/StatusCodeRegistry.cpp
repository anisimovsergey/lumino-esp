#include "StatusCodeRegistry.hpp"

using namespace Core;
using namespace Services;

int
StatusCodeRegistry::getCode(const Status& status) const {
  if (status.isOk())
    return 200;
  else
    return 500;
}
