#include "Status.hpp"

using namespace Core;

const Status Status::Ok =
  Status(true, "Success", "Success.");
const Status Status::NotSupported =
  Status(false, "NotSupported", "Not supported");
const Status Status::IncorrectObjectType =
  Status(false, "IncorrectObjectType", "Incorrect object type");
const Status Status::UnableToParseJson =
  Status(false, "UnableToParseJson", "Unable to parse JSON.");
const Status Status::ValueIsNotString =
  Status(false, "ValueIsNotString", "Value is not string.");
const Status Status::ValueIsNotBool =
  Status(false, "ValueIsNotBool", "Value is not boolean.");
const Status Status::UnableToFindSerializer =
  Status(false, "UnableToFindSerializer", "Unable to find serializer.");
const Status Status::UnableToScanFiFiNetworks =
  Status(false, "UnableToScanFiFiNetworks", "Unable to scan FiFi networks.");

Status::Status(bool ok, String code, String title) :
  ok(ok), code(code), title(title) {
}

Status
Status::UnableToFindJsonKey(String key) {
  return Status(false, "UnableToFindJsonKey", "Unable to find JSON key """ + key + """.");
}
