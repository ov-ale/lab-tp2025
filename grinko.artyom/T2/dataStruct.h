#ifndef DataStructH
#define DataStructH

#include <cmath>
#include <cstdint>

#include <iostream>
#include <string>

struct DataStruct {
    double_t key1{};
    int64_t key2{};
    std::string key3{};
};

std::ostream &operator<<(std::ostream &, const DataStruct &);
std::istream &operator>>(std::istream &, DataStruct &);

#endif
