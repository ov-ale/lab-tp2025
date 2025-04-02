#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>

class StreamGuard {
public:
    explicit StreamGuard(std::ostream& os);
    ~StreamGuard();

    StreamGuard(const StreamGuard&) = delete;
    StreamGuard& operator=(const StreamGuard&) = delete;

private:
    std::ostream& stream;
    std::ios::fmtflags flags;
    char fill;
    std::streamsize precision;
};

#endif
