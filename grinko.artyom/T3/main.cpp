#include <cstdint>
#include <cstdlib>

#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <utility>
#include <vector>

#include "geometry.h"
#include "command.h"

int32_t main(int32_t argc, char **argv) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    std::ifstream file{argv[1]};
    if (!file) {
        return EXIT_FAILURE;
    }

    Polygons polygons{};
    while (!file.eof()) {
        std::copy(std::istream_iterator<Polygon>{file},
                  std::istream_iterator<Polygon>{},
                  std::back_inserter(polygons));

        if (!file) {
            file.clear();
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (true) {
        Command command{};
        std::cin >> command;

        if (!std::cin) {
            if (std::cin.eof()) {
                break;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        std::cout << command(polygons) << std::endl;
    }

    return EXIT_SUCCESS;
}
