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
    // From ISerializer
    virtual String getTypeId() const override {
      return Core::StatusResult::TypeId;
    }

  protected:
    // From Serializer
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::StatusResult& statusResult,
      ISerializationContext& context) const override;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<Core::StatusResult>& statusResult,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_STATUS_SERIALIZER_HPP */
