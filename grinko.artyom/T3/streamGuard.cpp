#include "streamGuard.h"

StreamGuard::StreamGuard(std::ios &stream): stream{stream},
                                            flags{stream.flags()},
                                            precision{stream.precision()} {}

StreamGuard::~StreamGuard() {
    this->stream.flags(this->flags);
    this->stream.precision(this->precision);
}
