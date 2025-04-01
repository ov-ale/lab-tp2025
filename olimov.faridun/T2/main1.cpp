#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

#include "dataStruct.h"

int main() {
    std::vector<DataStruct> data;

    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<DataStruct>{std::cin},
            std::istream_iterator<DataStruct>{},
            std::back_inserter(data)
        );

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) {
            return a.key1 < b.key1;
        }

        const double aMagnitude = std::abs(a.key2);
        const double bMagnitude = std::abs(b.key2);
        if (aMagnitude != bMagnitude) {
            return aMagnitude < bMagnitude;
        }

        return a.key3.length() < b.key3.length();
        });

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>{std::cout, "\n"}
    );

    return 0;
}
