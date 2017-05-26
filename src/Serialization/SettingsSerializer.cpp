#include "SettingsSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_IS_ON "isOn"
#define FIELD_UNIQUE_NAME "uniqueName"
#define FIELD_DEVICE_NAME "deviceName"

Core::Status
SettingsSerializer::serializeImpl(ISerializationContext& context, const Settings& settings) const {
  auto result = context.setBool(FIELD_IS_ON, settings.getIsOn());
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_UNIQUE_NAME, settings.getUniqueName());
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_DEVICE_NAME, settings.getDeviceName());
  if (!result.isOk())
    return result;

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Settings>>
SettingsSerializer::deserializeImpl(
  const IDeserializationContext& context) const {
  Status result;

  bool isOn;
  std::tie(result, isOn) = context.getBool(FIELD_IS_ON);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::string deviceName;
  std::tie(result, deviceName) = context.getString(FIELD_DEVICE_NAME);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto settings = std::make_unique<Settings>(isOn, "", deviceName);
  return std::make_tuple(Status::OK, std::move(settings));
}
