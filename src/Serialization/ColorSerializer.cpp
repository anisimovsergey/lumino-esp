#include "ColorSerializer.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_RED     "r"
#define FIELD_GREEN   "g"
#define FIELD_BLUE    "b"

Core::Status
ColorSerializer::serialize(
  const Color& color,
  ISerializationContext& context) const {

  auto result = context.setInt(FIELD_RED, color.getR());
  if (!result.isOk())
    return result;

  result = context.setInt(FIELD_GREEN, color.getG());
  if (!result.isOk())
    return result;

  result = context.setInt(FIELD_BLUE, color.getB());
  if (!result.isOk())
    return result;

  return Status::OK;
}

Core::Status
ColorSerializer::deserialize(
  Models::Color::Unique& color,
  IDeserializationContext& context) const {

  int r, g, b;
  auto result = context.getInt(FIELD_RED, r);
  if (!result.isOk())
    return result;

  result = context.getInt(FIELD_GREEN, g);
  if (!result.isOk())
    return result;

  result = context.getInt(FIELD_BLUE, b);
  if (!result.isOk())
    return result;

  color = Color::makeUnique(r, g, b);
  return Status::OK;
}
