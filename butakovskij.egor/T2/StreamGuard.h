#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>

class StreamGuard {
public:
    StreamGuard(std::ios &stream);
    ~StreamGuard();

private:
    std::ios& stream_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::ios::fmtflags flags_;
};

#endif
