#include "DisplaySign.hpp"

using namespace Services;

const DisplaySign DisplaySign::Undefined = DisplaySign(-1);
const DisplaySign DisplaySign::Connected = DisplaySign(0);
const DisplaySign DisplaySign::Disconnected = DisplaySign(1);

DisplaySign::DisplaySign(int i) : i(i) {
}
