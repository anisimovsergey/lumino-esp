// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_SERVICE_HPP
#define JSON_SERIALIZATION_SERVICE_HPP

#include "ISerializer.hpp"
#include "ISerializationService.hpp"
#include "ISerializationContextFactory.hpp"

#include <memory>
#include <list>

namespace Json {

class SerializationService : public ISerializationService {
  public:
    SerializationService(
      std::shared_ptr<const ISerializationContextFactory> contextFactory);

    std::unique_ptr<Core::StatusResult> serialize(
      const Core::IEntity& entity,
      String& json) const override;

    std::unique_ptr<Core::StatusResult> serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const override;

    std::unique_ptr<Core::StatusResult> deserialize(
      const String& json,
      std::unique_ptr<Core::IEntity>& entity) const override;

    void addSerializer(
      std::shared_ptr<const ISerializer> serializer);

  private:
    std::shared_ptr<const ISerializationContextFactory>   contextFactory;
    std::list<std::shared_ptr<const ISerializer>>         serializers;

    std::shared_ptr<const ISerializer> getSerialzier(
      String typeId) const;
};

}

#endif /* end of include guard: SERVICES_SERIALIZATION_SERVICE_HPP */
