#include "DataStruct.h"
#include "StreamGuard.h"

#include <iomanip>
#include <sstream>

namespace {
    struct ReadOct {
        unsigned long long& ref;
        explicit ReadOct(unsigned long long& r) : ref(r) {}
    };

    struct ReadHex {
        unsigned long long& ref;
        explicit ReadHex(unsigned long long& r) : ref(r) {}
    };

    struct ReadStr {
        std::string& ref;
        explicit ReadStr(std::string& r) : ref(r) {}
    };

    struct Expect {
        char ch;
        explicit Expect(char c) : ch(c) {}
    };

    std::istream& operator>>(std::istream& in, Expect expect) {
        char got;
        in >> got;
        if (got != expect.ch) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, ReadOct oct) {
        StreamFmtGuard guard(in);
        in >> std::oct >> oct.ref;
        return in;
    }

    std::istream& operator>>(std::istream& in, ReadHex hex) {
        StreamFmtGuard guard(in);
        in >> std::hex >> hex.ref;
        return in;
    }

    std::istream& operator>>(std::istream& in, ReadStr str) {
        return std::getline(in >> Expect('"'), str.ref, '"');
    }
}

std::istream& operator>>(std::istream& in, Record& rec) {
    Record tmp{};
    bool ok1 = false, ok2 = false, ok3 = false;

    in >> Expect('(') >> Expect(':');
    for (int i = 0; i < 3; ++i) {
        std::string key;
        in >> key;
        if (!in) return in;

        if (key == "key1") {
            in >> ReadOct(tmp.key1);
            ok1 = true;
        }
        else if (key == "key2") {
            in >> ReadHex(tmp.key2);
            ok2 = true;
        }
        else if (key == "key3") {
            in >> ReadStr(tmp.key3);
            ok3 = true;
        }
        else {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> Expect(':');
    }
    in >> Expect(')');

    if (ok1 && ok2 && ok3) {
        rec = tmp;
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const Record& rec) {
    StreamFmtGuard guard(out);
    out << "(:key1 0" << std::oct << rec.key1
        << ":key2 0x" << std::uppercase << std::hex << rec.key2
        << ":key3 \"" << rec.key3 << "\":)";
    return out;
}
