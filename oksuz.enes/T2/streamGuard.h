#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>

class streamGuard {
    std::ios& stream;
    std::ios::fmtflags flags;
    std::streamsize precision;

public:
    streamGuard(std::ios& s);
    ~streamGuard();
};

#endif