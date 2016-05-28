// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SETTINGS_SERIALIZER_H
#define JSON_SETTINGS_SERIALIZER_H

#include "Core/Serializer.hpp"
#include "Models/Settings.hpp"

namespace Json {

class SettingsSerializer : public Core::Serializer<Models::Settings> {
  public:
    Models::Settings deserialize(const Core::ISerializationContext& context);

  protected:
    void serialize(const Models::Settings& settings,
                  Core::ISerializationContext& context) override;
};

}

#endif /* end of include guard: JSON_SETTINGS_SERIALIZER_H */
