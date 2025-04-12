#ifndef NSPACE_H
#define NSPACE_H
#include <string>
#include <iostream>


namespace nspace
{
    // формат ввода:
    // { "key1": 1.0d, "key2": -89LL, "key3": "Let madness release you" }
    struct Data {
        double key1 = 0.0;
        long long int key2 = 0;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };

    struct DoubleIO {
        double& ref;
    };

    struct SignedIO {
        long long int& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    struct LabelIO {
        std::string exp;
    };

    // scope guard для возврата состояния потока в первоначальное состояние
    class iofmtguard {
    public:
        iofmtguard(std::basic_ios< char >& s):
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
        std::basic_ios< char >& s_;
        std::streamsize width_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, SignedIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, Data& dest);
    std::ostream& operator<<(std::ostream& out, const Data& dest);
}


#endif // !NSPACE_H

