// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_SERVICE_H
#define JSON_SERIALIZATION_SERVICE_H

#include "ISerializer.hpp"
#include "ISerializationService.hpp"
#include "ISerializationContextFactory.hpp"

#include <memory>
#include <list>

namespace Json {

class SerializationService : public ISerializationService {
  public:
    SerializationService(const ISerializationContextFactory& contextFactory);

    String serialize(const Core::IEntity& entity) const override;
    void serialize(const Core::IEntity& entity,
                   ISerializationContext& context) const override;

    void addSerializer(std::shared_ptr<const ISerializer> serializer);

  private:
    const ISerializationContextFactory&              contextFactory;
    std::list<std::shared_ptr<const ISerializer>>       serializers;
};

}

#endif /* end of include guard: SERVICES_SERIALIZATION_SERVICE_H */
