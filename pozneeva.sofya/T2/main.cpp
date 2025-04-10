#include "nspace.h"
#include "sort.h"
#include <vector>
#include <iterator>
#include <sstream>
#include <cassert>


//DBL LIT SLL LIT
int main() {
    using nspace::Data;

    std::vector< Data > data;
    std::istringstream iss;
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator< Data >(std::cin),
            std::istream_iterator< Data >(),
            std::back_inserter(data)
        );

        std::copy(
            std::istream_iterator< Data >(iss),
            std::istream_iterator< Data >(),
            std::back_inserter(data)
        );
    }
    sort(data);
    std::cout << "Data:\n";
    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< Data >(std::cout, "\n")
    );

    return 0;
}

