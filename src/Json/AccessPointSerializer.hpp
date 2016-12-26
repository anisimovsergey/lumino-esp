// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_ACCESS_POINT_SERIALIZER_HPP
#define JSON_ACCESS_POINT_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Models/AccessPoint.hpp"

namespace Json {

class AccessPointSerializer : public Serializer<Models::AccessPoint> {
  TYPE_PTRS(AccessPointSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Models::AccessPoint& accessPoint,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Models::AccessPoint::Unique& accessPoint,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_ACCESS_POINT_SERIALIZER_HPP */
