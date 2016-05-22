// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef ERRORS_H
#define ERRORS_H

#include <WString.h>

class Error {
public:
  Error(String code, String description);

private:
  String code;
  String description;
};

class Errors {
public:
    static const Error UnableToScanFiFiNetworks;
};

#endif /* end of include guard: ERRORS_H */
