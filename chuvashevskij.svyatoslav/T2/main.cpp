#include "structs.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<structs::Data> data;

    /*std::istream_iterator<Data> inputIt(std::cin);*/

    std::ifstream in;
    in.open("test.txt");
    if (in.is_open())
    {
        std::istream_iterator<structs::Data> inputIt(in);
        std::copy(inputIt, std::istream_iterator<structs::Data>(), std::back_inserter(data));

        structs::makeCorrect(data);

        std::sort(data.begin(), data.end());

        std::copy(
            std::begin(data),
            std::end(data),
            std::ostream_iterator<structs::Data>(std::cout, "\n")
        );
    }

}
