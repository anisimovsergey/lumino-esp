// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef SERIALIZATION_COLOR_SERIALIZER_HPP
#define SERIALIZATION_COLOR_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Color.hpp"

#include <memory>

namespace Serialization {

class ColorSerializer : public Serializer<Models::Color> {
  protected:
    virtual Core::Status serializeImpl(
      ISerializationContext& context,
      const Models::Color& color) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Models::Color>> deserializeImpl(
      const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_CONNECTION_SERIALIZER_HPP */
