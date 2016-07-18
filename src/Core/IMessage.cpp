#include "IMessage.hpp"

using namespace Core;

const ActionType ActionType::Unknown = ActionType("unknown");
const ActionType ActionType::Get = ActionType("get");
const ActionType ActionType::Create = ActionType("create");
const ActionType ActionType::Update = ActionType("update");
const ActionType ActionType::Delete = ActionType("delete");

Message::Message(ActionType actionType, String resource) :
  actionType(actionType), resource(resource) {
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

Request::Request(ActionType actionType, String resource,
  std::unique_ptr<IEntity> content) : Message(actionType, resource),
  content(std::move(content)) {

}

Response::Response(ActionType actionType, String resource,
  std::unique_ptr<StatusResult> result) : Message(actionType, resource),
  result(std::move(result)) {

}

Notification::Notification(ActionType actionType, String resource,
  std::unique_ptr<IEntity> result) : Message(actionType, resource),
  result(std::move(result)) {

}
