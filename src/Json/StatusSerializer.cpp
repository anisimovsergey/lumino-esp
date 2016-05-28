#include "StatusSerializer.hpp"
#include "Core/Status.hpp"

using namespace Json;
using namespace Core;

void
StatusSerializer::serialize(const Status& status,
                            ISerializationContext& context) {
  context.setType("status");
  context.setValue("code", status.getCode());
  context.setValue("title", status.getTitle());
}
