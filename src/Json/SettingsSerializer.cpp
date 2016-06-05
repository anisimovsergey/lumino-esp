#include "SettingsSerializer.hpp"

#include "Core/Status.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

Core::Status
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {
  context.setValue("name", settings.getDeviceName());
  return Status::Ok;
}

Core::Status
SettingsSerializer::deserialize(
  std::shared_ptr<Models::Settings>& settings,
  ISerializationContext& context) const {

  String deviceName;
  Status status = context.getStringValue("name", deviceName);
  if (!status.isOk())
    return status;

  settings = std::shared_ptr<Models::Settings>(new Settings(deviceName));
  return Status::Ok;
}
