// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SETTINGSSERIALIZER_H
#define SETTINGSSERIALIZER_H

class Settings;
class ISerializationContext;

class SettingsSerializer {
public:
  Settings deserialie(const ISerializationContext& context);
  void serialie(const Settings& settings, ISerializationContext& context);
};

#endif /* end of include guard: SETTINGSSERIALIZER_H */
