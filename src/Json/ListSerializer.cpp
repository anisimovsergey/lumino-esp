#include "ListSerializer.hpp"

using namespace Json;
using namespace Core;

void
ListSerializer::serialize(
  const IList& list,
  ISerializationContext& context) const {

  context.setValue("elements", list);
}

Status
ListSerializer::deserialize(
  std::shared_ptr<IList>& list,
  ISerializationContext& context) const {

  return Status::NotSupported;
}
