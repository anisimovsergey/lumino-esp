#include "SerializationContext.hpp"

#include "Serialization/ISerializationService.hpp"

using namespace Core;
using namespace Serialization;

namespace {

  class StringBuilder : public Print {
   public:
    StringBuilder(std::string &str) : str(str) {}

    virtual size_t write(uint8_t c) {
      str += static_cast<char>(c);
      return 1;
    }

   private:
    StringBuilder &operator=(const StringBuilder &);

    std::string &str;
  };

}

SerializationContext::SerializationContext(
  const ISerializationService& serializationService,
  std::shared_ptr<const DynamicJsonBuffer> jsonBuffer,
  JsonObject& jsonObject) :
    serializationService(serializationService),
    jsonBuffer(jsonBuffer),
    jsonObject(jsonObject) {
}

std::string
SerializationContext::toString() const {
  std::string str;
  str.reserve(jsonObject.measureLength());
  StringBuilder strBuilder(str);
  jsonObject.printTo(strBuilder);
  return str;
}

Core::Status
SerializationContext::setString(const std::string& key, const std::string& value) {
  jsonObject[key] = value;
  return Status::OK;
}

Core::Status
SerializationContext::setInt(const std::string& key, int value) {
  jsonObject[key] = value;
  return Status::OK;
}

Core::Status
SerializationContext::setBool(const std::string& key, bool value) {
  jsonObject[key] = value;
  return Status::OK;
}

Core::Status
SerializationContext::setList(const std::string& key, const IList& list) {
  auto& array = jsonObject.createNestedArray(key);
  return list.forEach([&](const IEntity& element) {
    auto& nestedObject = array.createNestedObject();
    SerializationContext context(serializationService, jsonBuffer, nestedObject);
    auto result = serializationService.serialize(element, context);
    if (!result.isOk()) {
      return Status(StatusCode::InternalServerError,
        "Unable to serialize an element of the list.", std::move(result));
    }
    return Status::OK;
  });
}

Core::Status
SerializationContext::setEntity(const std::string& key, const Core::IEntity& entity) {
  auto& nestedObject = jsonObject.createNestedObject(key);
  SerializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.serialize(entity, context);
  if (!result.isOk()) {
      return Status(StatusCode::InternalServerError,
        "Unable to serialize a nested entity.", std::move(result));
  }
  return Status::OK;
}
