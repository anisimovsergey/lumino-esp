#include "Status.hpp"

Status::Status(bool ok, String code, String title) :
  ok(ok), code(code), title(title) {

}

const Status Status::Ok =
  Status(true, "Success", "Success.");
const Status Status::UnableToScanFiFiNetworks =
  Status(false, "UnableToScanFiFiNetworks", "Unable to scan FiFi networks.");
