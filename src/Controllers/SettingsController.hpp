// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

class IHttpServer;

class SettingsController {
private:
  void onGetSettings();
  void onPutSettings();

public:
  void registerOn(IHttpServer& server);
};

#endif /* end of include guard: SETTINGSCONTROLLER_H */
