// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_STATUS_H
#define CORE_STATUS_H

#include "IEntity.hpp"

namespace Core {

class Status : public IEntity {
  public:
    // Well-known statuses
    static const Status Ok;
    static const Status UnableToScanFiFiNetworks;

  public:
    String getTypeId() const override { return "status"; }
    
    bool   isOk() const { return ok;  }
    String getCode() const { return code; };
    String getTitle() const { return title; };

  private:
    Status(bool isOk, String code, String title);

    bool    ok;
    String  code;
    String  title;
};

}

#endif /* end of include guard: CORE_STATUS_H */
