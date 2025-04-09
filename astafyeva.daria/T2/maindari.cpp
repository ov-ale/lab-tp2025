#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

#include "DataStruct.h"
#include "StreamGuard.h"

int main() {
    std::vector<Record> data;
    Record temp;

    while (true) {
        if (!(std::cin >> temp)) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        data.push_back(temp);
    }

    std::sort(data.begin(), data.end(),
              [](const Record& lhs, const Record& rhs) {
                  if (lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
                  if (lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
                  return lhs.key3.length() < rhs.key3.length();
              });

    for (std::size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << '\n';
    }

    return 0;
}
