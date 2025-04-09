#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

#include "dataStruct.h"

int main() {
    std::vector<DataStruct> dataStructs;
    
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<DataStruct>{std::cin},
            std::istream_iterator<DataStruct>{},
            std::back_inserter(dataStructs)
        );

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(
        std::begin(dataStructs),
        std::end(dataStructs),
        [](const DataStruct &a, const DataStruct &b) {
            if (a.key1 != b.key1) return a.key1 < b.key1;
            if (std::abs(a.key2) != std::abs(b.key2)) return std::abs(a.key2) < std::abs(b.key2);
            return a.key3.length() < b.key3.length();
        });

    std::copy(
        std::begin(dataStructs),
        std::end(dataStructs),
        std::ostream_iterator<DataStruct>{std::cout, "\n"}
    );

    return EXIT_SUCCESS;
}