#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "dataStruct.h"
#include "streamGuard.h"

int main() {
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        DataStruct temp;
        if (iss >> temp) {
            data.push_back(temp);
        }
    }

    std::sort(data.begin(), data.end(), compareData);

    StreamGuard guard(std::cout);
    std::copy(data.begin(), data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
