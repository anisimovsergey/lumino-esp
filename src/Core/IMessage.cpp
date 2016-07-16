#include "IMessage.hpp"

using namespace Core;

Message::Message(MessageType messageType, String resource) :
  messageType(messageType), resource(resource) {
}

void
Message::addTag(String tag, String value) {
  tags.push_back(std::make_tuple(tag, value));
}

String
Message::getTag(String tag) {
    for(auto tuple: tags) {
      if (std::get<0>(tuple) == tag)
        return std::get<1>(tuple);
    }
    return "";
}
