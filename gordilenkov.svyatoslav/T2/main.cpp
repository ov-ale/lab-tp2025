#include "dataStruct.h"
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<DataStruct> dataVec;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(dataVec));

    std::sort(dataVec.begin(), dataVec.end(), compareData);

    std::copy(dataVec.begin(), dataVec.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}