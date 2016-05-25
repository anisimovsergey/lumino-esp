// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef IWIFISERVICE_H
#define IWIFISERVICE_H

#include <list>

class Status;
class Network;

class IWiFiService {
public:
    virtual Status getWiFiNetworks(std::list<Network>& networks) const = 0;
};

#endif /* end of include guard: IWIFISERVICE_H */
