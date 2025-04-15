#ifndef GeometryH
#define GeometryH

#include <cmath>
#include <cstdint>

#include <iostream>
#include <vector>

struct Point {
    int32_t x = 0, y = 0;
};

using Points = std::vector<Point>;

struct Polygon {
    Points points{};
};

using Polygons = std::vector<Polygon>;

double_t shoelace(const Polygon &);

std::istream &operator>>(std::istream &, Polygon &);
std::ostream &operator<<(std::ostream &, const Polygon &);

#endif
