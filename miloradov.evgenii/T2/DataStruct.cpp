#include "DataStruct.h"
#include "StreamGuard.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

struct Separate {
    char expected{};
};

std::istream& operator>>(std::istream& stream, const Separate&& separate) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char expected{};
        stream >> expected;
        if (!stream || expected != separate.expected) {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}

struct SingleQuote {
    char& value;
};

std::istream& operator>>(std::istream& stream, SingleQuote&& sq) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char quote;
        stream >> quote;
        if (!stream || quote != '\'') {
            stream.setstate(std::ios::failbit);
            return stream;
        }
        stream >> sq.value;
        stream >> quote;
        if (!stream || quote != '\'') {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}

struct DoubleQuote {
    std::string& value;
};

std::istream& operator>>(std::istream& stream, DoubleQuote&& dq) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char quote;
        stream >> quote;
        if (!stream || quote != '"') {
            stream.setstate(std::ios::failbit);
            return stream;
        }
        std::getline(stream, dq.value, '"');
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, Data& data) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Data input{};
        bool key1{}, key2{}, key3{};
        
        stream >> Separate{'('};
        stream >> Separate{':'};

        for (size_t i = 0; i < 3; ++i) {
            std::string key{};
            stream >> key;
            if (!stream) {
                return stream;
            }

            if (key == "key1") {
                stream >> input.key1 >> Separate{'d'};
                key1 = true;
            } else if (key == "key2") {
                stream >> Separate{'\''} >> input.key2 >> Separate{'\''};
                key2 = true;
            } else if (key == "key3") {
                stream >> Separate{'"'};
                std::getline(stream, input.key3, '"');
                key3 = true;
            } else {
                stream.setstate(std::ios::failbit);
                return stream;
            }

            stream >> Separate{':'};
        }

        stream >> Separate{')'};

        if (stream && key1 && key2 && key3) {
            data = input;
        } else {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Data& data) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        StreamGuard streamGuard{stream};
        stream << "(:key1 " << data.key1 << "d:key2 '" 
               << data.key2 << "':key3 \"" << data.key3 << "\":)";
    }
    return stream;
}