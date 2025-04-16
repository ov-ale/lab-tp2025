#ifndef GUARD_H
#define GUARD_H

#include <iostream>
#include <string>


namespace nspace
{
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios<char>& s) :
            s_(s),
            width_(s.width()),
            fill_(s.fill()),
            precision_(s.precision()),
            fmt_(s.flags())
        {}

        ~iofmtguard()
        {
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
}
#endif
