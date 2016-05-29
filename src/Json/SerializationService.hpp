// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_SERVICE_H
#define JSON_SERIALIZATION_SERVICE_H

#include "ISerializer.hpp"
#include "ISerializationService.hpp"

#include <memory>
#include <list>

namespace Json {

class SerializationService : public ISerializationService {
  public:
    void serialize(const Core::IEntity& object,
                   ISerializationContext& context) const override;

    void addSerializer(std::shared_ptr<ISerializer> serializer);

  private:
    std::list<std::shared_ptr<ISerializer>> serializers;
};

}

#endif /* end of include guard: SERVICES_SERIALIZATION_SERVICE_H */
