#include "compare_data.h"

bool compareData(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        if (a.key2.first * b.key2.second != b.key2.first * a.key2.second)
        {
            return a.key2.first * b.key2.second < b.key2.first * a.key2.second;
        }
    }
    return a.key3.length() < b.key3.length();
}
