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
    static const Status Conflict;
    static const Status NotSupported;
    static const Status IncorrectObjectType;
    static const Status UnableToParseJson;
    static const Status ValueIsNotString;
    static const Status ValueIsNotBool;
    static const Status UnableToFindSerializer;
    static const Status ResourceNotFound;
    static const Status ResourceCreated;
    static const Status UnableToConnect;
    static const Status UnableToScanFiFiNetworks;

    static Status UnableToFindJsonKey(String key);

  public:
    Status();

    static String getStaticTypeId() { return "status"; }

    bool   isOk() const { return ok;  }
    String getId() const { return id; };
    int    getCode() const { return code; }
    String getTitle() const { return title; };

  private:
    Status(String id, int code, String title);
    Status(bool ok, String id, int code, String title);

    bool    ok;
    String  id;
    int     code;
    String  title;
};

}

#endif /* end of include guard: CORE_STATUS_H */
