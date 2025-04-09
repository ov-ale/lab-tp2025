#include "structs.h"
#include "ScopeGuard.h"
#include <limits>
#include <cmath>

namespace structs
{
    const int ULL_MAX_SIZE = sizeof(std::numeric_limits<unsigned long long>::max()) * 8;
    std::istream& operator>>(std::istream& in, Separator&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '0';
        in >> c;
        if (in && c != dest.sep)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Mantissa&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string strMantissa;
        char i = '0';
        in >> i;
        if (!isdigit(i))
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        for (; isdigit(i) || i == '.'; in >> i)
        {
            strMantissa.push_back(i);
        }
        if (i != 'e' && i != 'E')
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        double mantissa = stod(strMantissa);
        if (mantissa >= 10 || mantissa < 1)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        dest.ref = mantissa;
        return in;
    }

    std::istream& operator>>(std::istream& in, Order&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, Label&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, ULLBin&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> Separator{ '0' } >> Separator{ 'b' };
        std::string bin;
        std::getline(in, bin, ':');
        int size = bin.size();
        if (size > ULL_MAX_SIZE)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        for (int i = 0; i < size; i++)
        {
            if (bin[i] != '0' && bin[i] != '1')
            {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        dest.ref = bin;
        return in;
    }

    std::istream& operator>>(std::istream& in, SDouble&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        double mantissa = 0.0;
        int order = 0;
        in >> Mantissa{ mantissa };
        in >> Order{ order };
        dest.ref = mantissa * std::pow(10, order);
        return in;
    }

    std::istream& operator>>(std::istream& in, String&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::getline(in >> Separator{ '"' }, dest.ref, '"');
        return in;
    }

    std::istream& operator>>(std::istream& in, Data& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Data input;
        in >> Separator{ '(' } >> Separator{ ':' };
        std::string label;
        bool key1f = false;
        bool key2f = false;
        bool key3f = false;
        while (in >> Label{ label })
            if (label == "key1" && !key1f)
            {
                in >> SDouble{ input.key1 };
                in >> Separator{ ':' };
                key1f = true;
            }
            else if (label == "key2" && !key2f)
            {
                in >> ULLBin{ input.key2 };
                key2f = true;
            }
            else if (label == "key3" && !key3f)
            {
                in >> String{ input.key3 };
                in >> Separator{ ':' };
                key3f = true;
            }
            else if (key1f && key2f && key3f)
            {
                if (label != ")")
                {
                    in.setstate(std::ios::failbit);
                }
                break;
            }
            else
            {
                in.setstate(std::ios::failbit);
                return in;
            }
        dest = input;
        if (!in)
        {
            dest.isCorrect = false;
            dest.key1 = 0.0;
            dest.key2 = "0";
            dest.key3 = "";
            in.clear();
            in.ignore(10000, '\n');
        }
        return in;
    }


    std::ostream& operator<<(std::ostream& out, const Data& dest)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        ScopeGuard guard(out);
        out << "(:key1 ";
        out << std::scientific << dest.key1;
        out << ":key2 0b";
        out << dest.key2;
        out << ":key3 ";
        out << '"' << dest.key3 << '"';
        out << ":)";
        return out;
    }

    void makeCorrect(std::vector<Data>& data)
    {
        int size = data.size();
        for (int i = 0; i < size; i++)
        {
            if (!data[i].isCorrect)
            {
                data.erase(data.begin() + i);
                i--;
                size--;
            }
        }
    }
}

