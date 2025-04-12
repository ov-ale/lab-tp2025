#include <cstdlib>
#include <cstdint>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

#include "dataStruct.h"

int32_t main() {
    using DataStructs = std::vector<DataStruct>;

    DataStructs dataStructs{};
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
            if (a.key1 < b.key1) {
                return true;
            } else if (a.key1 > b.key1) {
                return false;
            }

            if (a.key2 < b.key2) {
                return true;
            } else if (a.key2 > b.key2) {
                return false;
            }

            return a.key3.length() < b.key3.length();
        });

    std::copy(
        std::begin(dataStructs),
        std::end(dataStructs),
        std::ostream_iterator<DataStruct>{std::cout, "\n"}
    );

    return EXIT_SUCCESS;
}
