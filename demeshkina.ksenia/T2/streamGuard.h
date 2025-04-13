#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>
#include <iomanip>

class StreamGuard
{
public:
    explicit StreamGuard(std::ios &stream)
        : stream_(stream), flags_(stream.flags()), precision_(stream.precision()) {}

    ~StreamGuard()
    {
        stream_.flags(flags_);
        stream_.precision(precision_);
    }

private:
    std::ios &stream_;
    std::ios::fmtflags flags_;
    std::streamsize precision_;
};

#endif
