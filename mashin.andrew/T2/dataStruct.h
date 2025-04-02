#ifndef DATA_STRUCT
#define DATA_STRUCT

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <tuple>

namespace nspace {
    struct DataStruct {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };

    struct CharIO {
        char& ref;
    };

    struct LongLongIO {
        long long& ref;
    };

    struct UnsLongLongIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    bool comparator(const DataStruct& left, const DataStruct& right);

    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char>& s) :
            s_(s),
            width_(s.width()),
            fill_(s.fill()),
            precision_(s.precision()),
            fmt_(s.flags())
        {}

        ~iofmtguard() {
            s_.width(width_);
            s_.fill(fill_);
            s_.precision(precision_);
            s_.flags(fmt_);
        }
    private:
        std::basic_ios<char>& s_;
        std::streamsize width_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, CharIO&& dest);
    std::istream& operator>>(std::istream& in, LongLongIO&& dest);
    std::istream& operator>>(std::istream& in, UnsLongLongIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif