// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef NETWORKSCONTROLLER_H
#define NETWORKSCONTROLLER_H

class IHttpServer;

class NetworksController {
private:
  void onGetWiFiNetworks();

public:
  void registerOn(IHttpServer& server);
};

#endif /* end of include guard: NETWORKSCONTROLLER_H */
