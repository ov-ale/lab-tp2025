#include "dataStruct.h"
#include "streamGuard.h"

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <utility>

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

struct HexULL {
    unsigned long long &reference;
};

std::istream &operator>>(std::istream &stream, const HexULL &&hexULL) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        stream >> std::hex >> hexULL.reference;
        if (!stream) {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}

struct ComplexNumber {
    std::complex<double> &reference;
};

std::istream &operator>>(std::istream &stream, const ComplexNumber &&complex) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        double real{}, imag{};
        stream >> Delimiter{'#'} >> Delimiter{'c'} >> Delimiter{'('}
               >> real >> imag >> Delimiter{')'};
        if (stream) {
            complex.reference = std::complex<double>(real, imag);
        }
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
            if (!stream) break;

            if (key == "key1") {
                stream >> Delimiter{'0'} >> DelimiterOr{{'x', 'X'}} >> HexULL{result.key1};
                key1 = true;
            } else if (key == "key2") {
                stream >> ComplexNumber{result.key2};
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
               << "key1 0x" << std::hex << std::uppercase << dataStruct.key1 << ":"
               << "key2 #c(" << dataStruct.key2.real() << " " << dataStruct.key2.imag() << "):"
               << "key3 \"" << dataStruct.key3 << "\":"
               << ")";
    }
    return stream;
}