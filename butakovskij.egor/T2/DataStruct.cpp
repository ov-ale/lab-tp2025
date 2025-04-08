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

struct TripleDelimiterOr {
    char expectedFirst[3];
    char expectedSecond[3];
};

std::istream& operator>>(std::istream& is, TripleDelimiterOr&& tripleDelimiterOr) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }

    char expected[3];
    is >> expected[0] >> expected[1] >> expected[2];

    if (is &&
        (expected[0] != tripleDelimiterOr.expectedFirst[0] ||
            expected[1] != tripleDelimiterOr.expectedFirst[1] ||
            expected[2] != tripleDelimiterOr.expectedFirst[2]) &&
            (expected[0] != tripleDelimiterOr.expectedSecond[0] ||
            expected[1] != tripleDelimiterOr.expectedSecond[1] ||
            expected[2] != tripleDelimiterOr.expectedSecond[2])) {

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
    return is >> ullLit.value >> TripleDelimiterOr{{'u', 'l', 'l'}, {'U', 'L', 'L'}};
}

struct OctULL {
    unsigned long long& value;
};

std::istream& operator>>(std::istream& is, OctULL&& octULL) {
    std::istream::sentry sentry(is);
    if (!sentry) {
        return is;
    }

    char zero;
    if(!(is >> zero) || zero != '0') {
        is.setstate(std::ios::failbit);
        return is;
    }
    StreamGuard guard(is);
    if(!(is >> std::oct >> octULL.value)) {
        is.setstate(std::ios::failbit);
    }
    return is;
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
    ds.key1 << "ull:key2 0" <<
    std::oct << ds.key2 << ":key3 \"" <<
    std::dec << ds.key3 << "\":" << ")";
    return os;
}
