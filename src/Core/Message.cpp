#include "Message.hpp"

using namespace Core;

Message::Message(std::string sender, std::string receiver,
  ActionType actionType, std::string resource, Priority priority) :
  sender(sender), receiver(receiver),
  actionType(actionType), resource(resource), priority(priority) {
}
