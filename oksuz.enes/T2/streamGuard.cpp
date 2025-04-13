#include "streamGuard.h"

streamGuard::streamGuard(std::ios& s) :
    stream(s),
    flags(s.flags()),
    precision(s.precision()) {}

streamGuard::~streamGuard() {
    stream.precision(precision);
    stream.flags(flags);
}