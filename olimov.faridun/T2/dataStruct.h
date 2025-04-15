#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <complex>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <algorithm>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

unsigned long long parseOctal(const std::string& str);

std::complex<double> parseComplex(const std::string& str);

std::istream& operator>>(std::istream& in, DataStruct& data);

std::ostream& operator<<(std::ostream& out, const DataStruct& data);

bool compareData(const DataStruct& lhs, const DataStruct& rhs);

#endif
