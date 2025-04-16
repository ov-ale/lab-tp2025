#ifndef DATA_STRUCT 
#define DATA_STRUCT

#include <iostream>
#include <string>
#include <complex>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);

bool compareData(const DataStruct& a, const DataStruct& b);

#endif
