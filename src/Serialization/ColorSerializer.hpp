// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_COLOR_SERIALIZER_HPP
#define SERIALIZATION_COLOR_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Color.hpp"

namespace Serialization {

class ColorSerializer : public Serializer<Models::Color> {
  TYPE_PTRS(ColorSerializer)
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const Models::Color& color,
      ISerializationContext& context) const override;

    virtual Core::Status deserialize(
      Models::Color::Unique& color,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_CONNECTION_SERIALIZER_HPP */
