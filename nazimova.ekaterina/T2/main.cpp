#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "data_struct.h"
#include "io_operators.h"
#include "compare_data.h"

int main() {
    std::vector<DataStruct> dataVector;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        DataStruct data;
        if (iss >> data) {
            dataVector.push_back(data);
        }
    }

    std::sort(dataVector.begin(), dataVector.end(), compareData);

    for (const auto& data : dataVector) {
        std::cout << data << std::endl;
    }

    return 0;
}
