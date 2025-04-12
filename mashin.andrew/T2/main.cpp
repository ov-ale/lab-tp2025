#include "dataStruct.h"

int main() {
    using nspace::DataStruct;

    std::vector<DataStruct> data;
    while (!std::cin.eof()) {
        if (!std::cin) {
            std::cin.clear();
        }

        std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(), std::back_inserter(data));
    }

    std::sort(data.begin(), data.end(), nspace::comparator);

    std::copy(std::begin(data), std::end(data), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
