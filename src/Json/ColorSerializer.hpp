// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_COLOR_SERIALIZER_HPP
#define JSON_COLOR_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Models/Color.hpp"

namespace Json {

class ColorSerializer : public Serializer<Models::Color> {
  TYPE_PTRS(ColorSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Models::Color& color,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Models::Color::Unique& color,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_CONNECTION_SERIALIZER_HPP */
