// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_LIST_SERIALIZER_HPP
#define JSON_LIST_SERIALIZER_HPP

#include "Core/List.hpp"
#include "Serializer.hpp"

namespace Json {

class ListSerializer : public Serializer<Core::IList> {
  protected:
    // From Serializer
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::IList& list,
      ISerializationContext& context) const override;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
     std::unique_ptr<Core::IList>& list,
     ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_LIST_SERIALIZER_HPP */
