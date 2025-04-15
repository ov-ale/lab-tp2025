#ifndef MaxH
#define MaxH

#include <cmath>
#include <cstddef>

#include <algorithm>
#include <functional>
#include <numeric>
#include <type_traits>

#include "command.h"
#include "geometry.h"

struct MinAndMax {
    enum class Type {
        Area,
        Vertices
    };
};

template<MinAndMax::Type Type>
struct isArea: std::false_type {};

template<>
struct isArea<MinAndMax::Type::Area>: std::true_type{};

template<MinAndMax::Type Type>
struct isVertices: std::false_type {};

template<>
struct isVertices<MinAndMax::Type::Vertices>: std::true_type{};

template<MinAndMax::Type Type>
typename std::enable_if<isArea<Type>::value,
                        Command::Result>::type
max(const Polygons &polygons) {
    if (polygons.size() == 0) {
        return Command::Result{Command::Result::Type::InvalidCommand};
    }

    Command::Result result{Command::Result::Type::Real};
    std::vector<double_t> areas{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(areas),
                   shoelace);

    result.value.real = *std::max_element(std::begin(areas),
                                         std::end(areas));

    return result;
}

template<MinAndMax::Type Type>
typename std::enable_if<isVertices<Type>::value,
                        Command::Result>::type
max(const Polygons &polygons) {
    if (polygons.size() == 0) {
        return Command::Result{Command::Result::Type::InvalidCommand};
    }

    Command::Result result{Command::Result::Type::Size};
    std::vector<size_t> vertices{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(vertices),
                   [](const Polygon &polygon) {
                       return polygon.points.size();
                   });

    result.value.size = *std::max_element(std::begin(vertices),
                                          std::end(vertices));

    return result;
}

template<MinAndMax::Type Type>
typename std::enable_if<isArea<Type>::value,
                        Command::Result>::type
min(const Polygons &polygons) {
    if (polygons.size() == 0) {
        return Command::Result{Command::Result::Type::InvalidCommand};
    }

    Command::Result result{Command::Result::Type::Real};
    std::vector<double_t> areas{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(areas),
                   shoelace);

    result.value.real = *std::min_element(std::begin(areas),
                                         std::end(areas));

    return result;
}

template<MinAndMax::Type Type>
typename std::enable_if<isVertices<Type>::value,
                        Command::Result>::type
min(const Polygons &polygons) {
    if (polygons.size() == 0) {
        return Command::Result{Command::Result::Type::InvalidCommand};
    }

    Command::Result result{Command::Result::Type::Size};
    std::vector<size_t> vertices{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(vertices),
                   [](const Polygon &polygon) {
                       return polygon.points.size();
                   });

    result.value.size = *std::min_element(std::begin(vertices),
                                          std::end(vertices));

    return result;
}

#endif
