#include "ListSerializer.hpp"

using namespace Json;
using namespace Core;

void
ListSerializer::serialize(const IList& list,
                          ISerializationContext& context) {
    context.setValue("elements", list);
/*    auto& collection = context.createArray("elements");
    list.forEach([&](const ISerializable& element) {
      collection.addElement(element);
    }); */
}
