#include "IMessage.hpp"

using namespace Core;

const MessageType MessageType::Unknown = MessageType("unknown");
const MessageType MessageType::Get = MessageType("get");
const MessageType MessageType::Create = MessageType("create");
const MessageType MessageType::Update = MessageType("update");
const MessageType MessageType::Delete = MessageType("delete");

Message::Message(MessageType messageType, String resource) :
  messageType(messageType), resource(resource) {
}

void
Message::addTag(String tag, String value) {
  tags.push_back(std::make_tuple(tag, value));
}

String
Message::getTag(String tag) const {
    for(auto tuple: tags) {
      if (std::get<0>(tuple) == tag)
        return std::get<1>(tuple);
    }
    return "";
}

Response::Response(std::unique_ptr<Core::StatusResult> result) :
  messageType(MessageType::Unknown), resource(""), result(std::move(result)) {

}

Response::Response(std::unique_ptr<Core::StatusResult> result,
         MessageType messageType, String resource) :
         messageType(messageType), resource(resource), result(std::move(result)) {

}
