#include "ColorSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

#define FIELD_RED     "r"
#define FIELD_GREEN   "g"
#define FIELD_BLUE    "b"

Core::StatusResult::Unique
ColorSerializer::serialize(
  const Color& color,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_RED, color.getR());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_GREEN, color.getG());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_BLUE, color.getB());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
ColorSerializer::deserialize(
  Models::Color::Unique& color,
  ISerializationContext& context) const {

  int r, g, b;
  auto result = context.getIntValue(FIELD_RED, r);
  if (!result->isOk())
    return result;

  result = context.getIntValue(FIELD_GREEN, g);
  if (!result->isOk())
    return result;

  result = context.getIntValue(FIELD_BLUE, b);
  if (!result->isOk())
    return result;

  color = Color::makeUnique(r, g, b);
  return StatusResult::OK();
}
