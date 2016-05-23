// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef IWIFIMANAGER_H
#define IWIFIMANAGER_H

class IWiFiManager {
public:
  virtual bool isConnected() = 0;
  virtual void connect() = 0;
  virtual void disconnect() = 0;
};

#endif /* end of include guard: IWIFIMANAGER_H */
