#include "StreamGuard.h"

#include <ios>

StreamGuard::StreamGuard(std::ios &stream): stream{stream}, flags{std::move(stream.flags())} {}
StreamGuard::~StreamGuard() {
	stream.flags(this->flags);
}
