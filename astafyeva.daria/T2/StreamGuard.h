#ifndef UNIQUE_STREAMFMTGUARD_H
#define UNIQUE_STREAMFMTGUARD_H

#include <ios>

class StreamFmtGuard {
    std::ios& stream;
    std::ios::fmtflags oldFlags;

public:
    explicit StreamFmtGuard(std::ios& s);
    ~StreamFmtGuard();
};

#endif
