#include "QueueController.hpp"
#include "IMessageQueue.hpp"

using namespace Core;

QueueController::QueueController(std::string controllerId, IMessageQueue& messageQueue) :
  controllerId(controllerId), messageQueue(messageQueue) {

}

StatusResult::Unique
QueueController::sendNotification(std::string receiver, Notification::Shared notification) {
  notification->addTag("sender", controllerId);
  notification->addTag("receiver", receiver);
  return messageQueue.sendMessage(notification);
}

StatusResult::Unique
QueueController::broadcastNotification(Notification::Shared notification) {
  notification->addTag("sender", controllerId);
  return messageQueue.sendMessage(notification);
}

bool
QueueController::canProcessRequest(const Request& request) {
  if (canProcessRequestHandler)
    return canProcessRequestHandler(request);
  return false;
}

ActionResult::Unique
QueueController::processRequest(const Request& request) {
  if (processRequestHandler)
    return processRequestHandler(request);
  return StatusResult::NotImplemented();
}
