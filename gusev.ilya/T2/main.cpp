#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.h"
#include "comparison.h"

int main() {
    std::vector<DataStruct> dataVector;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector)
    );

    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    std::copy(
        dataVector.begin(),
        dataVector.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
