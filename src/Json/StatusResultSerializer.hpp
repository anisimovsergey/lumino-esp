// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_STATUS_SERIALIZER_HPP
#define JSON_STATUS_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/ActionResult.hpp"

namespace Json {

class StatusResultSerializer : public Serializer<Core::StatusResult> {
  public:
    String getTypeId() const override {
      return Core::StatusResult::getStaticTypeId();
    }

  protected:
    virtual std::shared_ptr<Core::IActionResult> serialize(
      const Core::StatusResult& statusResult,
      ISerializationContext& context) const override;

    virtual std::shared_ptr<Core::IActionResult> deserialize(
      std::shared_ptr<Core::StatusResult>& statusResult,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_STATUS_SERIALIZER_HPP */
