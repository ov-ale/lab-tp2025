#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>
#include <ostream>

class StreamGuard {
public:
    explicit StreamGuard(std::ostream& os)
    : stream(os), flags(os.flags()), fill(os.fill()), precision(os.precision()) {}
    ~StreamGuard(){
        stream.flags(flags);
        stream.fill(fill);
        stream.precision(precision);
    }

    StreamGuard(const StreamGuard&) = delete;
    StreamGuard& operator=(const StreamGuard&) = delete;

private:
    std::ostream& stream;
    std::ios::fmtflags flags;
    char fill;
    std::streamsize precision;

};


#endif
