#include "StreamGuard.h"
#include <ostream>

StreamGuard::StreamGuard(std::ostream& os)
    : stream(os), flags(os.flags()), fill(os.fill()), precision(os.precision()) {}

StreamGuard::~StreamGuard() {
    stream.flags(flags);
    stream.fill(fill);
    stream.precision(precision);
}