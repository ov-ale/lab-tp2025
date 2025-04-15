#include "geometry.h"

#include <cmath>

#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <utility>

double_t shoelace(const Polygon &polygon, size_t index) {
    size_t size = polygon.points.size();

    if (index == size + 1) {
        return 0;
    }

    int32_t x = polygon.points[index % size].x;
    int32_t xAhead = polygon.points[(index + 1) % size].x;
    int32_t y = polygon.points[index % size].y;
    int32_t yAhead = polygon.points[(index + 1) % size].y;

    return (y + yAhead) * (x - xAhead) +
           shoelace(polygon, index + 1);
}

double_t shoelace(const Polygon &polygon) {
    return std::abs(shoelace(polygon, 0)) / 2;
}

struct Delimiter {
    char expected = '\0';
};

std::istream &operator>>(std::istream &stream, const Delimiter &&delimiter) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char input = '\0';
        stream >> input;

        if (!stream || input != delimiter.expected) {
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}

std::istream &operator>>(std::istream &stream, Point &point) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Point input{};
        stream >> Delimiter{'('} >>
                  input.x >>
                  Delimiter{';'} >>
                  input.y >>
                  Delimiter{')'};

        if (stream) {
            point = std::move(input);
        }
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Point &point) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        stream << '(' << point.x << ';' << point.y << ')';
    }

    return stream;
}

std::istream &operator>>(std::istream &stream, Polygon &polygon) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Polygon input{};
        size_t numberOfPoints = 0;
        stream >> numberOfPoints;
        if (!stream || numberOfPoints < 3) {
            stream.setstate(std::ios::failbit);

            return stream;
        }

        std::copy_n(std::istream_iterator<Point>(stream),
                    numberOfPoints,
                    std::back_inserter(input.points));

        if (stream) {
            polygon = std::move(input);
        }
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Polygon &polygon) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        stream << polygon.points.size() << ' ';
        std::copy(std::begin(polygon.points),
                  std::end(polygon.points),
                  std::ostream_iterator<Point>{stream, " "});
    }

    return stream;
}
