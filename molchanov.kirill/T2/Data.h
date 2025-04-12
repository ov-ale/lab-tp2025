#ifndef LAB_TP2025_DATA_H
#define LAB_TP2025_DATA_H

#include <iostream>
#include <string>

struct Data {
    unsigned long long key1{};
    unsigned long long key2{};
    std::string key3{};
};

std::istream &operator>>(std::istream &stream, Data &data);
std::ostream &operator<<(std::ostream &stream, const Data &data);

#endif //LAB_TP2025_DATA_H
