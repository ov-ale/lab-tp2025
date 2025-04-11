#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>
#include <tuple>

namespace nspace
{
    struct DataStruct
    {
        double key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };
}

#endif