#ifndef CommandH
#define CommandH

#include <cmath>
#include <cstddef>

#include <functional>
#include <iostream>
#include <vector>

#include "geometry.h"

struct Command {
    struct Result {
        enum class Type {
            Real,
            Size,
            InvalidCommand
        };

        union Value {
            double_t real;
            size_t size;
        };

        Type type{};
        Value value{};
    };

    Result operator()(const Polygons &) const;

    friend std::istream &operator>>(std::istream &, Command &);

private:
    std::function<Result(const Polygons &)> command{};
};

std::ostream &operator<<(std::ostream &, const Command::Result &);

#endif
