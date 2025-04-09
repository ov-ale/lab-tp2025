#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

namespace nspace {
    struct Data {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };

    struct ULLLitIO {
        unsigned long long& ref;
    };

    struct ULLHexIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    struct LabelIO {
        std::string exp;
    };

    bool comprarator(Data& first, Data& second);

    class iofmtguard {
        public:
            iofmtguard(std::basic_ios<char>& s);
            ~iofmtguard();
        private:
            std::basic_ios<char>& s_;
            std::streamsize width_;
            char fill_;
            std::streamsize precision_;
            std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, ULLLitIO&& dest);
    std::istream& operator>>(std::istream& in, ULLHexIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, Data& dest);
    std::ostream& operator<<(std::ostream& out, const Data& dest);
};