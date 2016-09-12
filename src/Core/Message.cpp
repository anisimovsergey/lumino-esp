#include "Message.hpp"

using namespace Core;

Message::Message(ActionType actionType, std::string resource, Priority priority) :
  actionType(actionType), resource(resource), priority(priority) {
}

void
Message::addTag(std::string tag, std::string value) {
  tags.push_back(std::make_tuple(tag, value));
}

std::string
Message::getTag(std::string tag) const {
    for(auto tuple: tags) {
      if (std::get<0>(tuple) == tag)
        return std::get<1>(tuple);
    }
    return "";
}
