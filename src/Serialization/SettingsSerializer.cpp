#include "SettingsSerializer.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_NAME "name"

Core::Status
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {

  auto result = context.setString(FIELD_NAME, settings.getDeviceName());
  if (!result.isOk())
    return result;

  return Status::OK;
}

Core::Status
SettingsSerializer::deserialize(
  Models::Settings::Unique& settings,
  IDeserializationContext& context) const {

  std::string deviceName;
  auto result = context.getString(FIELD_NAME, deviceName);
  if (!result.isOk())
    return result;

  settings = Models::Settings::makeUnique(deviceName);
  return Status::OK;
}
