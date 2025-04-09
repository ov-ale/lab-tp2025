#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <complex>
#include <cstdint>
#include <iostream>
#include <string>

struct DelimiterOr {
    char expected[2]{};
};

struct DataStruct {
    unsigned long long key1;  // ULL HEX
    std::complex<double> key2; // CMP LSP
    std::string key3;
};

std::ostream &operator<<(std::ostream &, const DataStruct &);
std::istream &operator>>(std::istream &, DataStruct &);

#endif // DATASTRUCT_H