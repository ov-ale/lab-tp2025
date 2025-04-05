#include "StreamGuard.h"

StreamGuard::StreamGuard(std::ios& stream) :
    stream_{stream},
    width_{stream.width()},
    fill_{stream.fill()},
    precision_{stream.precision()},
    flags_{stream.flags()}
{}

StreamGuard::~StreamGuard() {
    stream_.width(width_);
    stream_.fill(fill_);
    stream_.flags(flags_);
    stream_.precision(precision_);
}
