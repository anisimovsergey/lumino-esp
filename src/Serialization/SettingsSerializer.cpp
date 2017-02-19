#include "SettingsSerializer.hpp"

#include "Core/Memory.hpp"

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
  std::unique_ptr<Settings>& settings,
  IDeserializationContext& context) const {

  std::string deviceName;
  auto result = context.getString(FIELD_NAME, deviceName);
  if (!result.isOk())
    return result;

  settings = std::make_unique<Settings>(deviceName);
  return Status::OK;
}
