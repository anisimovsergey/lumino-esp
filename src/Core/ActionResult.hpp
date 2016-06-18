// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_ACTION_RESULT_H
#define CORE_ACTION_RESULT_H

#include "Entity.hpp"

#include <memory>

namespace Core {

class ActionResult : public Entity<ActionResult> {
  public:
    // Well-known action results
    static std::shared_ptr<ActionResult> Success();
    static std::shared_ptr<ActionResult> Success(
      const std::shared_ptr<IEntity> entity);
    static std::shared_ptr<ActionResult> Conflict();
    static std::shared_ptr<ActionResult> NotSupported();
    static std::shared_ptr<ActionResult> IncorrectObjectType();
    static std::shared_ptr<ActionResult> UnableToParseJson();
    static std::shared_ptr<ActionResult> ValueIsNotAString();
    static std::shared_ptr<ActionResult> ValueIsNotABoolean();
    static std::shared_ptr<ActionResult> UnableToFindSerializer();
    static std::shared_ptr<ActionResult> ResourceNotFound();
    static std::shared_ptr<ActionResult> ResourceCreated();
    static std::shared_ptr<ActionResult> UnableToConnect();
    static std::shared_ptr<ActionResult> UnableToScanFiFiNetworks();
    static std::shared_ptr<ActionResult> UnableToFindJsonKey(String key);
    static std::shared_ptr<ActionResult> RedirectTo(String newResource);

  public:
    static String getStaticTypeId() { return "actionResult"; }

    bool   isOk() const { return ok;  }
    String getId() const { return id; };
    int    getCode() const { return code; }
    String getTitle() const { return title; };

  private:
    ActionResult(String id, int code, String title);
    ActionResult(String id, int code, String title, bool ok);

    bool    ok;
    String  id;
    int     code;
    String  title;
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_H */
