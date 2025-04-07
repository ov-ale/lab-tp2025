#include "dataStruct.h"
#include "streamGuard.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>



struct Delimiter {
    char expected;
};

std::istream& operator>>(std::istream& in, const Delimiter&& d) {
    char c{};
    in >> c;
    if (in && c != d.expected) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct quotedString {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, const quotedString&& q) {
    return std::getline(in >> Delimiter{ '"' }, q.ref, '"');
}

struct charLiteral {
    char& ref;
};

std::istream& operator>>(std::istream& in, const charLiteral&& cl) {
    char quote1{}, c{}, quote2{};
    in >> quote1 >> c >> quote2;
    if (in && quote1 == '\'' && quote2 == '\'') {
        cl.ref = c;
    }
    else {
        in.setstate(std::ios::failbit);
    }
    return in;
}


std::istream& operator>>(std::istream& in, dataStruct& ds) {
    std::istream::sentry s{ in };
    if (!s) return in;

    dataStruct result{};
    bool key1_found = false, key2_found = false, key3_found = false;

    std::string key;

    in >> Delimiter{ '(' } >> Delimiter{ ':' };

    for (int i = 0; i < 3; ++i) {
        in >> key;
        if (!in) break;

        if (key == "key1") {
            in >> result.key1;
            key1_found = true;
        }
        else if (key == "key2") {
            in >> charLiteral{ result.key2 };
            key2_found = true;
        }
        else if (key == "key3") {
            in >> quotedString{ result.key3 };
            key3_found = true;
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }

        in >> Delimiter{ ':' };
    }

    in >> Delimiter{ ')' };

    if (in && key1_found && key2_found && key3_found) {
        ds = std::move(result);
    }
    else {
        ds.invalid = true;
    }

    return in;
}


std::ostream& operator<<(std::ostream& out, const dataStruct& ds) {
    streamGuard guard(out);
    out << std::scientific << std::setprecision(3);
    out << "(:key1 " << ds.key1
        << ":key2 '" << ds.key2
        << "':key3 \"" << ds.key3 << "\":)";
    return out;
}
