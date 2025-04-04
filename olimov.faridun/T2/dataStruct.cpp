#include "dataStruct.h"
#include "streamGuard.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace {
    struct Delimiter {
        char expected;
    };

    std::istream& operator>>(std::istream& in, Delimiter&& delimiter) {
        std::istream::sentry sentry(in);
        if (sentry) {
            char actual;
            if (in >> actual && actual != delimiter.expected) {
                in.setstate(std::ios::failbit);
            }
        }
        return in;
    }

    struct ComplexNumber {
        std::complex<double>& value;
    };

    std::istream& operator>>(std::istream& in, ComplexNumber&& complex) {
        std::istream::sentry sentry(in);
        if (sentry) {
            double real, imag;
            in >> Delimiter{ '#' } >> Delimiter{ 'c' } >> Delimiter{ '(' }
            >> real >> Delimiter{ ' ' } >> imag >> Delimiter{ ')' };
            if (in) {
                complex.value = std::complex<double>(real, imag);
            }
        }
        return in;
    }

    struct OctalULL {
        unsigned long long& value;
    };

    std::istream& operator>>(std::istream& in, OctalULL&& octal) {
        std::istream::sentry sentry(in);
        if (sentry) {
            in >> std::oct >> octal.value;
            if (in) {
                in >> Delimiter{ ':' };
            }
        }
        return in;
    }

    struct StringValue {
        std::string& value;
    };

    std::istream& operator>>(std::istream& in, StringValue&& str) {
        std::istream::sentry sentry(in);
        if (sentry) {
            std::getline(in >> Delimiter{ '"' }, str.value, '"');
        }
        return in;
    }
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    DataStruct temp;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    in >> Delimiter{ '(' } >> Delimiter{ ':' };

    for (int i = 0; i < 3; ++i) {
        std::string key;
        in >> key;

        if (key == "key1") {
            in >> OctalULL{ temp.key1 };
            hasKey1 = true;
        }
        else if (key == "key2") {
            in >> ComplexNumber{ temp.key2 };
            hasKey2 = true;
        }
        else if (key == "key3") {
            in >> StringValue{ temp.key3 };
            hasKey3 = true;
        }
        else {
            in.setstate(std::ios::failbit);
        }

        in >> Delimiter{ ':' };
    }

    in >> Delimiter{ ')' };

    if (hasKey1 && hasKey2 && hasKey3) {
        data = temp;
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }

    StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);

    out << "(:key1 0" << std::oct << data.key1 << ":key2 #c("
        << data.key2.real() << " " << data.key2.imag() << "):key3 \""
        << data.key3 << "\":)";

    return out;
}
