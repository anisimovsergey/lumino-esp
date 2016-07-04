#include "MessageQueue.hpp"

using namespace Core;

void
MessageQueue::loop() {
  while (!actions.empty())
  {
    actions.front()();
    actions.pop();
  }
}

void
MessageQueue::post(TAction action) {
    actions.push(action);
}
