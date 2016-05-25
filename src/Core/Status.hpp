// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MOIKOT_CORE_STATUS_H
#define MOIKOT_CORE_STATUS_H

#include <WString.h>

class Status {
public:
  bool   isOk() const { return ok;  }
  String getCode() const { return code; };
  String getTitle() const { return title; };

  static const Status Ok;
  static const Status UnableToScanFiFiNetworks;

private:
  Status(bool isOk, String code, String title);

  bool    ok;
  String  code;
  String  title;
};


#endif /* end of include guard: MOIKOT_CORE_STATUS_H */
