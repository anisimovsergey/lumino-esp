#include "ColorSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_HUE         "h"
#define FIELD_SATURATION  "s"
#define FIELD_VOLUME      "v"

Core::Status
ColorSerializer::serializeImpl(
  ISerializationContext& context,
  const Color& color) const {

  auto result = context.setFloat(FIELD_HUE, color.getH());
  if (!result.isOk())
    return result;

  result = context.setFloat(FIELD_SATURATION, color.getS());
  if (!result.isOk())
    return result;

  result = context.setFloat(FIELD_VOLUME, color.getV());
  if (!result.isOk())
    return result;

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Models::Color>>
ColorSerializer::deserializeImpl(
  const IDeserializationContext& context) const {
  Status result;
  float h, s, v;
  std::tie(result, h) = context.getFloat(FIELD_HUE);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::tie(result, s) = context.getFloat(FIELD_SATURATION);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::tie(result, v) = context.getFloat(FIELD_VOLUME);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto color = std::make_unique<Color>(h, s, v);
  return std::make_tuple(Status::OK, std::move(color));
}
