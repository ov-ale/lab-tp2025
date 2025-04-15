#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

bool parseScientificDouble(const std::string& str, double& value);
bool parseLongLong(const std::string& str, long long& value);
std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif
