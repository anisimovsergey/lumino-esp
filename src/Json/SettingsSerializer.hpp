// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SETTINGS_SERIALIZER_HPP
#define JSON_SETTINGS_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Models/Settings.hpp"

namespace Json {

class SettingsSerializer : public Serializer<Models::Settings> {
  TYPE_PTRS(SettingsSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Models::Settings& settings,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Models::Settings::Unique& settings,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_SETTINGS_SERIALIZER_HPP */
