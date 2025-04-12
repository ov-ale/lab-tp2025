#ifndef StreamGuardH
#define StreamGuardH

#include <ios>

class StreamGuard {
    std::ios &stream;
    std::ios::fmtflags flags{};
    std::streamsize precision{};

public:
    StreamGuard(std::ios &);
    ~StreamGuard();
};

#endif
