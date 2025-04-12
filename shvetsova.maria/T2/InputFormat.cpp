#include "InputFormat.h"

namespace nspace
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '\0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> dest.ref;
        if (in.peek() == 'd')
        {
            in >> DelimiterIO{ 'd' };
        }
        else
        {
            in >> DelimiterIO{ 'D' };
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, UnsighLongLongIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> dest.ref;
        std::string suffix;
        char c = '\0';
        for (int i = 0; i < 3; ++i) {
            if (!(in >> c)) return in;
            suffix += std::tolower(c);
        }

        if (suffix != "ull") {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> DelimiterIO{ '"' };
        in >> dest.exp >> DelimiterIO{ '"' };
        return in;
    }
}
