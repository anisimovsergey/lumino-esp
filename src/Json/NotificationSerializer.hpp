// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_NOTIFICATION_SERIALIZER_HPP
#define JSON_NOTIFICATION_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/IMessage.hpp"

namespace Json {

class NotificationSerializer : public Serializer<Core::Notification> {
  protected:
    // From Serializer
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::Notification& notification,
      ISerializationContext& context) const override;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<Core::Notification>& notification,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_NOTIFICATION_SERIALIZER_HPP */
