#include "Message.hpp"

using namespace Core;

Message::Message(ActionType actionType, std::string resource, Priority priority) :
  actionType(actionType), resource(resource), priority(priority) {
}

void
Message::addTag(std::string tag, std::string value) {
  tags[tag] = value;
}

std::string
Message::getTag(std::string tag) const {
  auto entry = tags.find(tag);
  if (entry == tags.end())
    return "";

  return entry->second;
}
