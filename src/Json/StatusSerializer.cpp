#include "StatusSerializer.hpp"
#include "ISerializationContext.hpp"
#include "Core/Status.hpp"

Status
StatusSerializer::deserialie(const ISerializationContext& context) {
}

void
StatusSerializer::serialie(const Status& status, ISerializationContext& context) {

  context.setType("status");
  context.setValue("code", status.getCode());
  context.setValue("title", status.getTitle());
}
