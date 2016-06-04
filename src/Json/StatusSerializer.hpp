// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_STATUS_SERIALIZER_H
#define JSON_STATUS_SERIALIZER_H

#include "Serializer.hpp"
#include "Core/Status.hpp"

namespace Json {

class StatusSerializer : public Serializer<Core::Status> {
  public:
    String getTypeId() const override {
      return Core::Status::getStaticTypeId();
    }

  protected:
    Core::Status serialize(
      const Core::Status& status,
      ISerializationContext& context) const override;

    Core::Status deserialize(
      std::shared_ptr<Core::Status>& status,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_STATUS_SERIALIZER_H */
