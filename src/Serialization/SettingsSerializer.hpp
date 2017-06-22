// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef SERIALIZATION_SETTINGS_SERIALIZER_HPP
#define SERIALIZATION_SETTINGS_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Settings.hpp"

#include <memory>

namespace Serialization {

class SettingsSerializer : public Serializer<Models::Settings> {
  protected:
    virtual Core::Status serializeImpl(
      ISerializationContext& context,
      const Models::Settings& settings) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Models::Settings>> deserializeImpl(
      const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_SETTINGS_SERIALIZER_HPP */
