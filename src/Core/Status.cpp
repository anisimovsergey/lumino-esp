#include "Status.hpp"

using namespace Core;

const Status Status::Ok =
  Status(true, "Success", 200, "Success.");
const Status Status::Conflict =
  Status("Conflict", 409, "Conflict.");
const Status Status::NotSupported =
  Status("NotSupported", 501, "Not supported");
const Status Status::IncorrectObjectType =
  Status("IncorrectObjectType", 500, "Incorrect object type");
const Status Status::UnableToParseJson =
  Status("UnableToParseJson", 400, "Unable to parse JSON.");
const Status Status::ValueIsNotString =
  Status("ValueIsNotString", 400, "Value is not string.");
const Status Status::ValueIsNotBool =
  Status("ValueIsNotBool", 400, "Value is not boolean.");
const Status Status::UnableToFindSerializer =
  Status("UnableToFindSerializer", 500, "Unable to find serializer.");
const Status Status::ResourceNotFound =
  Status("ResourceNotFound", 404, "Unable to find requested resource.");
const Status Status::ResourceCreated =
  Status("ResourceCreated", 302, "The resource was created.");
const Status Status::UnableToConnect =
  Status("UnableToConnect", 500, "Unable to connect.");
const Status Status::UnableToScanFiFiNetworks =
  Status("UnableToScanFiFiNetworks", 500, "Unable to scan FiFi networks.");

Status::Status() :
  id("Undefined"),
  code(500),
  title("Undefined error") {
}

Status::Status(String id, int code, String title) :
  ok(false), id(id), code(code), title(title) {
}

Status::Status(bool ok, String id, int code, String title) :
  ok(ok), id(id), code(code), title(title) {
}

Status
Status::UnableToFindJsonKey(String key) {
  return Status("UnableToFindJsonKey", 400, "Unable to find JSON key """ + key + """.");
}
