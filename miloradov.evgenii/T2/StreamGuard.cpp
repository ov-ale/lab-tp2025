#include "StreamGuard.h"

StreamGuard::StreamGuard(std::ios& stream): stream{stream}, flags{stream.flags()} {}
StreamGuard::~StreamGuard() {
  stream.flags(flags);
}