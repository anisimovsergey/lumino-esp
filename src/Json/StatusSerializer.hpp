// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_STATUS_SERIALIZER_H
#define JSON_STATUS_SERIALIZER_H

#include "ISerializationContext.hpp"
#include "Core/Status.hpp"

namespace Json {

class StatusSerializer {
  public:
    Core::Status deserialie(const ISerializationContext& context);
    void serialie(const Core::Status& status,
                  ISerializationContext& context);
};

}

#endif /* end of include guard: JSON_STATUS_SERIALIZER_H */
