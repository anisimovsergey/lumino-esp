#include "SettingsSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

#define FIELD_NAME "name"

std::unique_ptr<Core::StatusResult>
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {

  auto result = context.setValue(FIELD_NAME, settings.getDeviceName());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SettingsSerializer::deserialize(
  std::unique_ptr<Models::Settings>& settings,
  ISerializationContext& context) const {

  String deviceName;
  auto result = context.getStringValue(FIELD_NAME, deviceName);
  if (!result->isOk())
    return result;

  settings = make_unique<Models::Settings>(deviceName);
  return StatusResult::OK();
}
