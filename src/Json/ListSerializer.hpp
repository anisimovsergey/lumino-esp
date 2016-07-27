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
  TYPE_PTRS(ListSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Core::IList& list,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
     Core::IList::Unique& list,
     ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_LIST_SERIALIZER_HPP */
