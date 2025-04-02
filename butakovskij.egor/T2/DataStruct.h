#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iosfwd>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

bool parseULLLit(const std::string& str, unsigned long long& value);
bool parseULLOct(const std::string& str, unsigned long long& value);
std::istream& operator>>(std::istream& is, DataStruct& ds);
std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
bool compare(const DataStruct& a, const DataStruct& b);

#endif
