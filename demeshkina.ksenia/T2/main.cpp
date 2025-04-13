#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "dataStruct.h"

int main()
{
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        DataStruct ds;

        if (iss >> ds)
        {
            data.push_back(ds);
        }
    }

    std::sort(data.begin(), data.end(), [](const DataStruct &a, const DataStruct &b)
    {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.size() < b.key3.size();
    });

    for (const auto &ds : data)
    {
        std::cout << ds << std::endl;
    }

    return 0;
}
