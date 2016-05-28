// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_LIST_SERIALIZER_H
#define JSON_LIST_SERIALIZER_H

#include "Core/Serializer.hpp"
#include "Core/List.hpp"

namespace Json {

class ListSerializer : public Core::Serializer<Core::IList> {
  protected:
    void serialize(const Core::IList& list,
                   Core::ISerializationContext& context) override;
};

}

#endif /* end of include guard: JSON_LIST_SERIALIZER_H */
