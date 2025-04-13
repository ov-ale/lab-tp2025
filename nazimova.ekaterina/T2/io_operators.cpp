#include "io_operators.h"

std::istream& operator>>(std::istream& in, DataStruct& data) {
    DataStruct temp;
    std::string input;

    if (!std::getline(in, input, '(')) return in;

    std::stringstream ss(input);
    std::string field, value;

    while (ss >> field) {
        if (field == ":key1") {
            ss >> std::quoted(value);
            if (value.length() == 3 && value[0] == '\'' && value[2] == '\'') {
                temp.key1 = value[1];
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (field == ":key2") {
            long long n;
            unsigned long long d;
            char tempChar;
            std::string tempStr;

            ss >> tempChar;
            if (tempChar != '(')
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            ss >> tempStr;
            if (tempStr != ":N")
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            ss >> n;
            ss >> tempStr;
            if (tempStr != ":D")
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            ss >> d;
            ss >> tempChar;
            if (tempChar != ':')
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            ss >> tempChar;
            if (tempChar != ')')
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            temp.key2 = { n, d };
        }
        else if (field == ":key3") {
            ss >> std::quoted(temp.key3);
        }
    }
    data = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 '" << data.key1 << "':key2 (:N " << data.key2.first
        << ":D " << data.key2.second << ":):key3 \"" << data.key3 << "\":)";
    return out;
}
