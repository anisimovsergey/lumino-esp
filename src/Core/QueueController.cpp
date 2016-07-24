#include "QueueController.hpp"
#include "IMessageQueue.hpp"

using namespace Core;

QueueController::QueueController(String controllerId, IMessageQueue& messageQueue) :
  controllerId(controllerId), messageQueue(messageQueue) {

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

IActionResult::Unique
QueueController::processRequest(const Request& request) {
  if (processRequestHandler)
    return processRequestHandler(request);
  StatusResult::NotImplemented();
}
