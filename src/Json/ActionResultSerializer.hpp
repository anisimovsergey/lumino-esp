// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_STATUS_SERIALIZER_H
#define JSON_STATUS_SERIALIZER_H

#include "Serializer.hpp"
#include "Core/ActionResult.hpp"

namespace Json {

class ActionResultSerializer : public Serializer<Core::ActionResult> {
  public:
    String getTypeId() const override {
      return Core::ActionResult::getStaticTypeId();
    }

  protected:
    virtual std::shared_ptr<Core::ActionResult> serialize(
      const Core::ActionResult& actionResult,
      ISerializationContext& context) const override;

    virtual std::shared_ptr<Core::ActionResult> deserialize(
      std::shared_ptr<Core::ActionResult>& actionResult,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_STATUS_SERIALIZER_H */
