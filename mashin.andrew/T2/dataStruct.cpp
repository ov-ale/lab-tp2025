#include "dataStruct.h"

namespace nspace {
    bool comparator(const DataStruct& left, const DataStruct& right) {
        return std::tie(left.key1, left.key2.first, left.key2.second, left.key3) <
            std::tie(right.key1, right.key2.first, right.key2.second, right.key3);
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char ch;
        in >> ch;
        if (in && (ch != dest.exp)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }


    std::istream& operator>>(std::istream& in, CharIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        std::string data;
        std::getline(in >> DelimiterIO { '\''}, data, '\'');
        if (data[0] != '\0' && data[1] == '\0') {
            dest.ref = data[0];
        }
        else {
            in.setstate(std::ios::failbit);
        }

        return in;
    }


    std::istream& operator>>(std::istream& in, LongLongIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        return in >> DelimiterIO{ 'N' } >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, UnsLongLongIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        return in >> DelimiterIO{ 'D' } >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        DataStruct input;
        bool fkey1 = false;
        bool fkey2 = false;
        bool fkey3 = false;

        using sep = DelimiterIO;
        using chr = CharIO;
        using ll = LongLongIO;
        using ull = UnsLongLongIO;
        using str = StringIO;

        in >> sep{ '(' };
        while (!(fkey1 && fkey2 && fkey3)) {
            std::string temp;
            char ch;

            in >> ch;
            if (!in) {
                break;
            }

            if (ch == ':' && (in >> temp)) {
                if (temp == "key1") {
                    in >> chr{ input.key1 };
                    fkey1 = true;
                }
                else if (temp == "key2") {
                    in >> sep{ '(' } >> sep{ ':' };
                    in >> ll{ input.key2.first } >> sep{ ':' } >> ull{ input.key2.second };
                    in >> sep{ ':' } >> sep{ ')' };
                    fkey2 = true;
                }
                else if (temp == "key3") {
                    in >> str{ input.key3 };
                    fkey3 = true;
                }
            }
        }
        in >> sep{ ':' } >> sep{ ')' };

        if (in) {
            dest = std::move(input);
        }

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        iofmtguard fmtguard(out);

        out << "(:";
        out << "key1 '" << src.key1 << "'";
        out << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
        out << ":key3 \"" << src.key3 << "\"";
        out << ":)";

        return out;
    }
}
