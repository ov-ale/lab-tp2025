// ULL LIT && ULL OCT
#include "DataStruct.h"
#include "StreamGuard.h"

#include <iostream>
#include <string>

struct Delimiter {
    char expected;
};

std::istream& operator>>(std::istream& is, Delimiter&& delimeter) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }
    char exp;
    is >> exp;
    if (is &&  (exp != delimeter.expected)) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

struct DelimiterOr {
    char expectedFirst;
    char expectedSecond;
};

std::istream& operator>>(std::istream& is, DelimiterOr&& delimiterOr) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }

    char exp;
    is >> exp;

    if(is &&
        (exp != delimiterOr.expectedFirst ||
             exp != delimiterOr.expectedSecond)) {
                is.setstate(std::ios::failbit);
        }
    return is;

}

struct DoubleDelimiterOr {
    char expectedFirst[2];
    char expectedSecond[2];
};

std::istream& operator>>(std::istream& is, DoubleDelimiterOr&& doubleDelimiterOr) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }

    char expected[2];
    is >> expected[0] >> expected[1];

    if (is &&
        (expected[0] != doubleDelimiterOr.expectedFirst[0] ||
            expected[1] != doubleDelimiterOr.expectedFirst[1]) &&
        (expected[0] != doubleDelimiterOr.expectedSecond[0] ||
            expected[1] != doubleDelimiterOr.expectedSecond[1])) {
                is.setstate(std::ios::failbit);
        }
    return is;
}

struct LitULL {
    unsigned long long& value;
};

std::istream& operator>>(std::istream& is, LitULL&& ullLit) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }
    return is >> ullLit.value >> DelimiterOr{'u', 'U'} >> DoubleDelimiterOr{{'l', 'l'}, {'L', 'L'}};
}

struct OctULL {
    unsigned long long& value;
};

std::istream& operator>>(std::istream& is, OctULL&& octULL) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }
    std::string svalue = std::to_string(octULL.value);
    for (char c : svalue) {
        if (c < '0' || c > '8') {
            is.setstate(std::ios_base::failbit);
        }
    }
    return is >> Delimiter{'0'} >> octULL.value;
}

struct String {
    std::string& value;
};

std::istream& operator>>(std::istream& is, String&& string) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }
    return std::getline(is >> Delimiter {'"'}, string.value, '"');
}

const size_t NUMBER_OF_KEYS = 3;

std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }
    DataStruct result;
    bool key1, key2, key3;

    is >> Delimiter{'('} >> Delimiter{':'};
    for (size_t i = 0; i < NUMBER_OF_KEYS; i++) {
        std::string key;
        is >> key;
        if (!is) {
            break;
        }

        if (key == "key1") {
            is >> LitULL{result.key1};
            key1 = true;
        }
        else if (key == "key2") {
            is >> OctULL{result.key2};
            key2 = true;
        }
        else if (key == "key3") {
            is >> String{result.key3};
            key3 = true;
        }
        else {
            is.setstate(std::ios::failbit);
            break;
        }
        is >> Delimiter{':'};
    }
    is >> Delimiter{')'};

    if (is && key1 && key2 && key3) {
        ds = std::move(result);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    std::ostream::sentry sentry(os);
    if (!sentry) {
        return os;
    }
    StreamGuard guard(os);

    os << "(:key1 " <<
    ds.key1 << ":key2 " <<
    ds.key2 << ":key3 " <<
    ds.key3 << "\":" << ")";
    return os;
}
