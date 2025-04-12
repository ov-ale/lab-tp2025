#ifndef LAB_TP2025_STREAMGUARD_H
#define LAB_TP2025_STREAMGUARD_H

#include <ios>

class StreamGuard {
    std::ios &stream;
    std::ios::fmtflags flags{};

public:
    StreamGuard(std::ios &stream);
    ~StreamGuard();
};


#endif //LAB_TP2025_STREAMGUARD_H
