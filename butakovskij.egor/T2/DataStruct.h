#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iostream>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& ds);
std::ostream& operator<<(std::ostream& os, const DataStruct& ds);

#endif
