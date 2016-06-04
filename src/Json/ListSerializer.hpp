// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_LIST_SERIALIZER_H
#define JSON_LIST_SERIALIZER_H

#include "Core/List.hpp"
#include "Serializer.hpp"

namespace Json {

class ListSerializer : public Serializer<Core::IList> {
  public:
    String getTypeId() const override {
      return Core::List<class T>::getStaticTypeId();
    }

  protected:
    Core::Status serialize(
      const Core::IList& list,
      ISerializationContext& context) const override;

   Core::Status deserialize(
     std::shared_ptr<Core::IList>& list,
     ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_LIST_SERIALIZER_H */
