// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_STATUS_H
#define CORE_STATUS_H

#include "Entity.hpp"

namespace Core {

class Status : public Entity<Status> {
  public:
    // Well-known statuses
    static const Status Ok;
    static const Status NotSupported;
    static const Status IncorrectObjectType;
    static const Status UnableToParseJson;
    static const Status ValueIsNotString;
    static const Status ValueIsNotBool;
    static const Status UnableToFindSerializer;
    static const Status UnableToScanFiFiNetworks;

    static Status UnableToFindJsonKey(String key);

  public:
    static String getStaticTypeId() { return "status"; }

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
