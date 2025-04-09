#include "dataStruct.h"
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<DataStruct> data;
    std::cout << "Вводи данные (Ctrl+Z/Ctrl+D для завершения):\n";

    DataStruct temp;
    while (std::cin >> temp)
    {
        data.push_back(temp);
    }

    std::cin.clear();

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    std::sort(data.begin(), data.end(), compareDataStructs);

    std::cout << "\nОтсортировано:\n";
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
