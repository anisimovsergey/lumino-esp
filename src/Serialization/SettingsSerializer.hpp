// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_SETTINGS_SERIALIZER_HPP
#define SERIALIZATION_SETTINGS_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Settings.hpp"

#include <memory>

namespace Serialization {

class SettingsSerializer : public Serializer<Models::Settings> {
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const Models::Settings& settings,
      ISerializationContext& context) const override;

    virtual Core::Status deserialize(
      std::unique_ptr<Models::Settings>& settings,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_SETTINGS_SERIALIZER_HPP */
