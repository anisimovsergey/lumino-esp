// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SETTINGS_SERIALIZER_H
#define JSON_SETTINGS_SERIALIZER_H

#include "ISerializationContext.hpp"
#include "Models/Settings.hpp"

namespace Json {

class SettingsSerializer {
  public:
    Models::Settings deserialie(const ISerializationContext& context);
    void serialie(const Models::Settings& settings,
                  ISerializationContext& context);
};

}

#endif /* end of include guard: JSON_SETTINGS_SERIALIZER_H */
