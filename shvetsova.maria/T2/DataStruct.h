#ifndef DATA_STRUCT
#define DATA_STRUCT
#include "InputFormat.h"
#include "ScopeGuard.h"
#include <iomanip>
#include <iostream>

// DBL LIT | ULL LIT
namespace nspace {
    struct DataStruct
    {
        double key1 = 0.0;
        unsigned long long key2 = 0ULL;
        std::string key3;
    };

    bool operator<(const DataStruct& obj1, const DataStruct& obj2);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif
