#include "nspace.h"
#include <iomanip>


namespace nspace {
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        // все перегрузки операторов ввода/вывода должны начинатьс€ с проверки экземпл€ра класса sentry
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }


    std::istream& operator>>(std::istream & in, DoubleIO && dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        return in >> dest.ref;
        in >> c;
        if (c == 'd' && c == 'D') { return in; }
    }


    std::istream& operator>>(std::istream& in, SignedIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        in >> dest.ref;
        std::string suffix;
        char c = '0';
        while (in >> c) {
            suffix += toupper(c);
        } 
        if (suffix != "ll") {
            return in;
        }
        return in >> dest.ref >> suffix;
    }


    std::istream& operator>>(std::istream& in, StringIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }


    std::istream& operator>>(std::istream& in, LabelIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        if ((in >> StringIO{ data }) && (data != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }


    std::istream& operator>>(std::istream& in, Data& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Data input;
        {
            using sep = DelimiterIO;
            using label = LabelIO;
            using dbl = DoubleIO;
            using sgn = SignedIO;
            using str = StringIO;
            in >> sep{ '{' };
            std::string key="0";
            while (!(in >> sep{ '}' })) {
                in >> key;
                if (key == "key1") {
                    in >> key >> sep{ ':' } >> dbl{ input.key1 };
                    in >> sep{ ',' };
                }
                else if (key == "key2") {
                    in >> key >> sep{ ':' } >> sgn{ input.key2 };
                    in >> sep{ ',' };
                }
                else { in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 }; }
            }
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }


    std::ostream& operator<<(std::ostream& out, const Data& dest) {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "{ ";
        out << "\"key1\": " << std::fixed << std::setprecision(1) << dest.key1 << "d, ";
        out << "\"key2\": " << dest.key2;
        out << " }";
        return out;
    }

}