#include "streamGuard.h"

#include <ios>

StreamGuard::StreamGuard(std::ios &stream):
    stream{stream},
    flags{stream.flags()},
    precision{stream.precision()} {}

StreamGuard::~StreamGuard() {
    this->stream.precision(this->precision);
    this->stream.flags(this->flags);
}