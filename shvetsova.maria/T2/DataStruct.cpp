#include "DataStruct.h"


namespace nspace{
    bool operator<(const DataStruct & obj1, const DataStruct & obj2) {
        if (obj1.key1 != obj2.key1) {
            return obj1.key1 < obj2.key1;
        }
        if (obj1.key2 != obj2.key2) {
            return obj1.key2 < obj2.key2;
        }
        return obj1.key3.size() < obj2.key3.size();
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        DataStruct input;
        {
            using sep = DelimiterIO;
            using ull = UnsighLongLongIO;
            using dbl = DoubleIO;
            using str = StringIO;
            in >> sep{ '(' };
            in >> sep{ ':' };
            for (int i = 0; i < 3; i++) {
                std::string key;
                in >> key;

                if (key == "key1") {
                    in >> dbl{ input.key1 };
                    in >> sep{ ':' };
                }

                else if (key == "key2") {
                    in >> ull{ input.key2 };
                    in >> sep{ ':' };
                }
                else if (key == "key3") {
                    in >> str{ input.key3 };
                    in >> sep{ ':' };
                }
                if (!sentry) {
                    return in;
                }
            }
            in >> sep{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest) {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d";
        out << ":key2 " << dest.key2 << "ull";
        out << ":key3 \"" << dest.key3 << "\":)";
        return out;
    }
}
