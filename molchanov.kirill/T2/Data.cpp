#include "Data.h"
#include <ios>
#include <iostream>


#include "StreamGuard.h"

struct Delimiter {
    char expected;
};

std::istream &operator>>(std::istream &stream, const Delimiter &&delimiter) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char actual{};
        stream >> actual;
        if (!stream || actual != delimiter.expected) {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}

struct Oct {
    unsigned long long &ref;
    Oct(unsigned long long& ref) : ref(ref) {}
};

struct Hex {
    unsigned long long &ref;
    Hex(unsigned long long& ref) : ref(ref) {}
};

struct String
{
    std::string& ref;
};

std::istream &operator>>(std::istream &stream, Oct &&ref) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        StreamGuard guard{stream};
        stream >> std::oct >> ref.ref;
    }
    return stream;
}

std::istream &operator>>(std::istream &stream, Hex &&ref) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        StreamGuard guard{stream};
        stream >> std::hex >> ref.ref;
    }
    return stream;
}

std::istream& operator>>(std::istream& in, String&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> Delimiter{ '"' }, dest.ref, '"');
}

std::istream &operator>>(std::istream &stream, Data &data) {
    std::istream::sentry sentry(stream);
    if (!sentry) return stream;

    Data input;
    bool hasKey1{}, hasKey2{}, hasKey3{};

    stream >> Delimiter{'('};
    stream >> Delimiter{':'};

    for (int i = 0; i < 3; ++i) {
        std::string key;
        stream >> key;
        if (!stream) return stream;

        if (key == "key1") {
            stream >> Oct{input.key1};
            hasKey1 = true;
        } else if (key == "key2") {
            stream >> Hex{input.key2};
            hasKey2 = true;
        } else if (key == "key3"){
            stream >> String{input.key3};
            hasKey3 = true;
        } else {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        stream >> Delimiter{':'};
    }

    stream >> Delimiter{')'};

    if (stream && hasKey1 && hasKey2 && hasKey3) {
        data = input;
    } else {
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Data &data) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        StreamGuard guard{stream};
        stream << "(:key1 0" << std::oct << data.key1
               << ":key2 0x" << std::uppercase << std::hex << data.key2
               << ":key3 \"" << data.key3 << "\"" << ":)";
    }
    return stream;
}
