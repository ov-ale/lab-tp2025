#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iostream>
#include <iomanip>

struct DataStruct {
    double key1;
    unsigned long long key2;
    std::string key3;
};

bool parseDoubleLiteral(const std::string& s, double& value);
bool parseHexLiteral(const std::string& s, unsigned long long& value);
bool parseQuotedString(const std::string& s, std::string& value);

std::istream& operator>>(std::istream& in, DataStruct& ds);
std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
bool compareDataStructs(const DataStruct& a, const DataStruct& b);

void runTests();

#endif