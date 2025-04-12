#include "dataStruct.h"

#include <cmath>
#include <cstddef>

#include <iomanip>
#include <ios>
#include <iostream>
#include <utility>

#include "streamGuard.h"

struct Delimiter {
    char expected{};
};

std::istream &operator>>(std::istream &stream, const Delimiter &&delimiter) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char expected{};
        stream >> expected;
        if (stream && expected != delimiter.expected) {
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}

struct DelimiterOr {
    char expected[2]{};
};

std::istream &operator>>(std::istream &stream, const DelimiterOr &&delimiterOr) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char expected{};
        stream >> expected;
        if (stream &&
            expected != delimiterOr.expected[0] &&
            expected != delimiterOr.expected[1]) {
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}

struct DoubleT {
    double_t &reference;
};

std::istream &operator>>(std::istream &stream, const DoubleT &&doubleT) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        stream >> doubleT.reference >> DelimiterOr{{'d', 'D'}};
    }

    return stream;
}

struct DoubleDelimiterOr {
    char expectedFirst[2]{};
    char expectedSecond[2]{};
};

std::istream &operator>>(std::istream &stream, const DoubleDelimiterOr &&doubleDelimiterOr) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char expected[2]{};
        stream >> expected[0] >> expected[1];
        if (stream &&
            (expected[0] != doubleDelimiterOr.expectedFirst[0] ||
                expected[1] != doubleDelimiterOr.expectedFirst[1]) &&
            (expected[0] != doubleDelimiterOr.expectedSecond[0] ||
                expected[1] != doubleDelimiterOr.expectedSecond[1])) {
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}

struct Int64T {
    int64_t &reference;
};

std::istream &operator>>(std::istream &stream, const Int64T &&int64T) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        stream >> int64T.reference >> DoubleDelimiterOr{{'l', 'l'}, {'L', 'L'}};
    }

    return stream;
}

struct String {
    std::string &reference;
};

std::istream &operator>>(std::istream &stream, const String &&string) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        std::getline(stream >> Delimiter{'"'}, string.reference, '"');
    }

    return stream;
}

const size_t NUMBER_OF_KEYS = 3;

std::istream &operator>>(std::istream &stream, DataStruct &dataStruct) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        bool key1{}, key2{}, key3{};
        DataStruct result{};

        stream >> Delimiter{'('} >> Delimiter{':'};
        for (size_t i = 0; i < NUMBER_OF_KEYS; ++i) {
            std::string key{};
            stream >> key;
            if (!stream) {
                break;
            }

            if (key == "key1") {
                stream >> DoubleT{result.key1};

                key1 = true;
            } else if (key == "key2") {
                stream >> Int64T{result.key2};

                key2 = true;
            } else if (key == "key3") {
                stream >> String{result.key3};

                key3 = true;
            } else {
                stream.setstate(std::ios::failbit);

                break;
            }

            stream >> Delimiter{':'};
        }
        stream >> Delimiter{')'};

        if (stream && key1 && key2 && key3) {
            dataStruct = std::move(result);
        }
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const DataStruct &dataStruct) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        StreamGuard streamGuard{stream};
        stream << std::fixed << std::setprecision(1) << "(:"
               << "key1 " << dataStruct.key1 << "d:"
               << "key2 " << dataStruct.key2 << "ll:"
               << "key3 \"" << dataStruct.key3 << "\":"
               << ")";
    }

    return stream;
}
