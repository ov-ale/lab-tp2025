#include "StreamGuard.h"

StreamFmtGuard::StreamFmtGuard(std::ios& s) : stream(s), oldFlags(s.flags()) {}
StreamFmtGuard::~StreamFmtGuard() {
    stream.flags(oldFlags);
}
