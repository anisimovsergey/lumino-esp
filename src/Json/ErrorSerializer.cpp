#include "ErrorSerializer.hpp"
#include "ISerializationContext.hpp"
#include "../Core/Error.hpp"

Error
ErrorSerializer::deserialie(const ISerializationContext& context) {
}

void
ErrorSerializer::serialie(const Error& error, ISerializationContext& context) {

  context.setType("error");
  context.setValue("code", error.getCode());
  context.setValue("title", error.getTitle());
}
