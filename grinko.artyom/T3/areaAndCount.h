#ifndef AreaH
#define AreaH

#include <cmath>
#include <cstddef>

#include <algorithm>
#include <functional>
#include <numeric>
#include <type_traits>

#include "command.h"
#include "geometry.h"

struct AreaAndCount {
    enum class Type {
        Even,
        Odd,
        Mean,
        NumberOfVertices
    };
};

template<AreaAndCount::Type Type>
struct isEven: std::false_type {};

template<>
struct isEven<AreaAndCount::Type::Even>: std::true_type{};

template<AreaAndCount::Type Type>
struct isOdd: std::false_type {};

template<>
struct isOdd<AreaAndCount::Type::Odd>: std::true_type{};

template<AreaAndCount::Type Type>
struct isMean: std::false_type {};

template<>
struct isMean<AreaAndCount::Type::Mean>: std::true_type{};

template<AreaAndCount::Type Type>
struct isNumberOfVertices: std::false_type {};

template<>
struct isNumberOfVertices<AreaAndCount::Type::NumberOfVertices>: std::true_type{};

template<AreaAndCount::Type Type>
typename std::enable_if<isEven<Type>::value,
                        Command::Result>::type
area(const Polygons &polygons) {
    Command::Result result{Command::Result::Type::Real};
    std::vector<double_t> areas{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(areas),
                   [](const Polygon &polygon) {
                       if (polygon.points.size() % 2 == 0) {
                           return shoelace(polygon);
                       }

                       return 0.0;
                   });

    result.value.real = std::accumulate(std::begin(areas),
                                        std::end(areas),
                                        0);

    return result;
}

template<AreaAndCount::Type Type>
typename std::enable_if<isOdd<Type>::value,
                        Command::Result>::type
area(const Polygons &polygons) {
    Command::Result result{Command::Result::Type::Real};
    std::vector<double_t> areas{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(areas),
                   [](const Polygon &polygon) {
                       if (polygon.points.size() % 2 != 0) {
                           return shoelace(polygon);
                       }

                       return 0.0;
                   });

    result.value.real = std::accumulate(std::begin(areas),
                                        std::end(areas),
                                        0);

    return result;
}

template<AreaAndCount::Type Type>
typename std::enable_if<isMean<Type>::value,
                        Command::Result>::type
area(const Polygons &polygons) {
    if (polygons.size() == 0) {
        return Command::Result{Command::Result::Type::InvalidCommand};
    }

    Command::Result result{Command::Result::Type::Real};
    std::vector<double_t> areas{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(areas),
                   shoelace);

    result.value.real = std::accumulate(std::begin(areas),
                                        std::end(areas),
                                        0);
    result.value.real /= polygons.size();

    return result;
}

template<AreaAndCount::Type Type>
typename std::enable_if<isNumberOfVertices<Type>::value,
                        Command::Result>::type
area(size_t numberOfVertices, const Polygons &polygons) {
    Command::Result result{Command::Result::Type::Real};
    std::vector<double_t> areas{};
    std::transform(std::begin(polygons),
                   std::end(polygons),
                   std::back_inserter(areas),
                   [&](const Polygon &polygon) {
                       if (numberOfVertices == polygon.points.size()) {
                           return shoelace(polygon);
                       }

                       return 0.0;
                   });

    result.value.real = std::accumulate(std::begin(areas),
                                        std::end(areas),
                                        0);

    return result;
}

template<AreaAndCount::Type Type>
typename std::enable_if<isEven<Type>::value,
                        Command::Result>::type
count(const Polygons &polygons) {
    Command::Result result{Command::Result::Type::Size};
    result.value.size = std::count_if(std::begin(polygons),
                                      std::end(polygons),
                                      [](const Polygon &polygon) {
                                          return polygon.points.size() % 2 == 0;
                                      });

    return result;
}

template<AreaAndCount::Type Type>
typename std::enable_if<isOdd<Type>::value,
                        Command::Result>::type
count(const Polygons &polygons) {
    Command::Result result{Command::Result::Type::Size};
    result.value.size = std::count_if(std::begin(polygons),
                                      std::end(polygons),
                                      [](const Polygon &polygon) {
                                          return polygon.points.size() % 2 != 0;
                                      });

    return result;
}

template<AreaAndCount::Type Type>
typename std::enable_if<isNumberOfVertices<Type>::value,
                        Command::Result>::type
count(size_t numberOfVertices, const Polygons &polygons) {
    Command::Result result{Command::Result::Type::Size};
    result.value.size = std::count_if(std::begin(polygons),
                                      std::end(polygons),
                                      [&](const Polygon &polygon) {
                                          return polygon.points.size() == numberOfVertices;
                                      });

    return result;
}

#endif
