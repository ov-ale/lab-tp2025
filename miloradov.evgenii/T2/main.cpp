#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"

bool compareData(const Data& a, const Data& b);

int main() {
    std::vector<Data> datas{};
    
    std::copy(
        std::istream_iterator<Data>{std::cin},
        std::istream_iterator<Data>{},
        std::back_inserter(datas)
    );

    std::sort(datas.begin(), datas.end(), compareData);
    
    std::copy(
        datas.begin(),
        datas.end(),
        std::ostream_iterator<Data>{std::cout, "\n"}
    );

    return EXIT_SUCCESS;
}

bool compareData(const Data& a, const Data& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}
