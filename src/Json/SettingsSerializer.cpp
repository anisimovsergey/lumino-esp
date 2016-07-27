#include "SettingsSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

#define FIELD_NAME "name"

Core::StatusResult::Unique
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {

  auto result = context.setValue(FIELD_NAME, settings.getDeviceName());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
SettingsSerializer::deserialize(
  Models::Settings::Unique& settings,
  ISerializationContext& context) const {

  String deviceName;
  auto result = context.getStringValue(FIELD_NAME, deviceName);
  if (!result->isOk())
    return result;

  settings = Models::Settings::makeUnique(deviceName);
  return StatusResult::OK();
}
