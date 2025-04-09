#include "DataStruct.h"

namespace nspace {
    std::istream& operator>>(std::istream& in, nspace::DelimiterIO&& dest) {
        char a;
        in >> a;
        if (a != dest.exp) {
                in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, nspace::ULLLitIO&& dest) {
        try {
            std::string a;
            size_t pos = 0;
            in >> a;
            dest.ref = std::stoull(a, &pos, 10);
            std::string check = a.substr(pos);
            if (check != "ULL" and check != "ull") {
                in.setstate(std::ios::failbit);
            }
        }
        catch (...) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, nspace::ULLHexIO&& dest) {
        try {
            std::string a;
            if (!(in >> a)) {
                in.setstate(std::ios::failbit);
            }
            if (a[0] != '0' or a[1] != 'x') {
                in.setstate(std::ios::failbit);
            }
            dest.ref = std::stoull(a.substr(2), nullptr, 16);
        } catch (...) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, nspace::StringIO&& dest) {
        char a;
        if (in >> a) {
            if (a != '"') {
                in.setstate(std::ios::failbit);
            }
        }
        else {
            in.setstate(std::ios::failbit);
        }
        std::getline(in, dest.ref, '"');
        return in;
    }

    std::istream& operator>>(std::istream& in, nspace::LabelIO&& dest) {
        std::string key;
        if (in >> key && key == dest.exp) {
            return in;
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    std::istream& operator>>(std::istream& in, nspace::Data& dest) {
        in >> nspace::DelimiterIO{'('} >> nspace::DelimiterIO{':'};
        int keysCount = 0;
        while (keysCount < 3 and in.good()) {
            std::string key;
            in >> key;
            if (key == "key1") {
                in >> nspace::ULLLitIO{dest.key1};
                in >> nspace::DelimiterIO{':'};
                keysCount++;
            }
            else if (key == "key2") {
                in >> nspace::ULLHexIO{dest.key2};
                in >> nspace::DelimiterIO{':'};
                keysCount++;
            }
            else if (key == "key3") {
                in >> nspace::StringIO{dest.key3};
                in >> nspace::DelimiterIO{':'};
                keysCount++;
            }
            else {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        if (keysCount != 3) {
            in.setstate(std::ios::failbit);
        }
        in >> nspace::DelimiterIO{')'};
        if (!in) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const nspace::Data& dest) {
        iofmtguard fmtguard(out);
        out << "Ключ 1 " << dest.key1 << std::endl << "Ключ 2 " << "0x" << std::uppercase << std::hex <<
            dest.key2 << std::endl << "Ключ 3 " << dest.key3 << std::endl;
        return out;
    }

    bool comparator(Data& first, Data& second) {
        if (first.key1 != second.key1) {
            return first.key1 < second.key1;
        }
        else if (first.key2 != second.key2) {
            return first.key2 < second.key2;
        } else {
            return first.key3.size() < second.key3.size();
        }
    }

    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
        s_(s),
        width_(s.width()),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
  {}

    iofmtguard::~iofmtguard()
    {
        s_.width(width_);
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }

}

int main() {
    using nspace::Data;
    std::vector<Data> data;
    while (!std::cin.eof()) {
        std::copy(std::istream_iterator<Data>(std::cin), std::istream_iterator<Data>(), std::back_inserter(data));
        if (!(std::cin)) {
            std::cin.clear();
            std::cin.ignore();
        }
    }

    std::sort(data.begin(), data.end(), nspace::comparator);
    std::copy(std::begin(data), std::end(data), std::ostream_iterator<Data>(std::cout, "\n"));
    return 0;

}