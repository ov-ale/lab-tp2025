#include "dataStruct.h"
#include "io.h"
#include "sort.h"
#include <iostream>
#include <iterator>
#include <limits>


int main()
{
    using nspace::DataStruct;

    std::vector<DataStruct> data;
    while (!std::cin.eof())
    {
        if (!std::cin)
        {
            std::cin.clear();
        }

        std::copy(std::istream_iterator<DataStruct>(std::cin),
                  std::istream_iterator<DataStruct>(),
                  std::back_inserter(data));
    }

    sortDataVector(data);

    std::copy(std::begin(data), std::end(data),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
