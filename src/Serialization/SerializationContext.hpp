// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_SERIALIZATION_CONTEXT_HPP
#define SERIALIZATION_SERIALIZATION_CONTEXT_HPP

#include "Serialization/ISerializationContext.hpp"

#include <ArduinoJson.h>

#include <memory>

namespace Serialization {

struct ISerializationService;

class SerializationContext : public ISerializationContext {
  public:
    SerializationContext(
      const ISerializationService& serializationService,
      std::shared_ptr<const DynamicJsonBuffer> jsonBuffer,
      JsonObject& jsonObject);

    // From ISerializationContext
    std::string toString() const override;

    virtual Core::Status
      setString(const std::string& key, const std::string& value) override;
    virtual Core::Status
      setInt(const std::string& key, int value) override;
    virtual Core::Status
      setBool(const std::string& key, bool value) override;
    virtual Core::Status
      setList(const std::string& key, const Core::IList& list) override;
    virtual Core::Status
      setEntity(const std::string& key, const Core::IEntity& entity) override;

  private:
    const ISerializationService&              serializationService;
    std::shared_ptr<const DynamicJsonBuffer>  jsonBuffer;
    JsonObject&                               jsonObject;
};

}

#endif /* end of include guard: SERIALIZATION_SERIALIZATION_CONTEXT_HPP */
