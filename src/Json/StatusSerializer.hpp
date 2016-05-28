// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_STATUS_SERIALIZER_H
#define JSON_STATUS_SERIALIZER_H

#include "Core/Serializer.hpp"
#include "Core/Status.hpp"

namespace Json {

class StatusSerializer : public Core::Serializer<Core::Status> {
  protected:
    void serialize(const Core::Status& status,
                   Core::ISerializationContext& context) override;
};

}

#endif /* end of include guard: JSON_STATUS_SERIALIZER_H */
