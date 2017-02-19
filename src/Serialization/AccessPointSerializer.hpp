// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_ACCESS_POINT_SERIALIZER_HPP
#define SERIALIZATION_ACCESS_POINT_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/AccessPoint.hpp"

#include <memory>

namespace Serialization {

class AccessPointSerializer : public Serializer<Models::AccessPoint> {
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const Models::AccessPoint& accessPoint,
      ISerializationContext& context) const override;

    virtual Core::Status deserialize(
      std::unique_ptr<Models::AccessPoint>& accessPoint,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_ACCESS_POINT_SERIALIZER_HPP */
