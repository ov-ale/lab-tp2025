#include "StreamGuard.h"

StreamGuard::StreamGuard(std::ios& stream) : stream{stream}, flags{stream.flags()}, precision{stream.precision()} {}

StreamGuard::~StreamGuard() {
	stream.precision(precision);
    stream.flags(flags);
}
