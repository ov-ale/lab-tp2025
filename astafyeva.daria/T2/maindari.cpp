#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "DataStruct.h"
#include "StreamGuard.h"

int main() {
    std::vector<Record> data;
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<Record>{std::cin},
            std::istream_iterator<Record>{},
            std::back_inserter(data)
        );
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(
        data.begin(),
        data.end(),
        [](Record data1, Record data2) {
            if (data1.key1 < data2.key1) {
                return true;
            }
            else if (data1.key1 > data2.key1) {
                return false;
            }
            if (data1.key2 < data2.key2) {
                return true;
            }
            else if (data1.key2 > data2.key2) {
                return false;
            }
            return data1.key3.length() < data2.key3.length();
        }
    );

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<Record>{std::cout, "\n"}
    );

    return EXIT_SUCCESS;
}