#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cmath>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

namespace Parser {
    bool parseHexValue(const std::string& str, unsigned long long& value) {
        if (str.size() < 3 || (str.substr(0, 2) != "0x" && str.substr(0, 2) != "0X")) {
            return false;
        }

        try {
            size_t pos = 0;
            value = std::stoull(str.substr(2), &pos, 16);
            return pos == str.size() - 2;
        } catch (...) {
            return false;
        }
    }

    bool parseComplexNumber(const std::string& str, std::complex<double>& value) {
        if (str.size() < 5 || str.substr(0, 3) != "#c(" || str.back() != ')') {
            return false;
        }

        std::istringstream iss(str.substr(3, str.size() - 4));
        double real, imag;
        if (!(iss >> real >> imag)) {
            return false;
        }
        value = std::complex<double>(real, imag);
        return true;
    }
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    if (!std::getline(in, line)) {
        return in;
    }

    if (line.empty() || line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    line = line.substr(1, line.size() - 2);
    size_t pos = 0;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    while (pos < line.size()) {
        while (pos < line.size() && std::isspace(line[pos])) {
            pos++;
        }
        if (pos >= line.size()) {
            break;
        }

        if (line[pos] != ':') {
            in.setstate(std::ios::failbit);
            return in;
        }
        pos++;

        size_t fieldEnd = line.find(' ', pos);
        if (fieldEnd == std::string::npos) {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::string fieldName = line.substr(pos, fieldEnd - pos);
        pos = fieldEnd + 1;

        size_t valueEnd = line.find(':', pos);
        if (valueEnd == std::string::npos) {
            valueEnd = line.size();
        }

        std::string fieldValue = line.substr(pos, valueEnd - pos);
        pos = valueEnd;

        if (fieldName == "key1") {
            if (!Parser::parseHexValue(fieldValue, data.key1)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey1 = true;
        } else if (fieldName == "key2") {
            if (!Parser::parseComplexNumber(fieldValue, data.key2)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey2 = true;
        } else if (fieldName == "key3") {
            if (fieldValue.size() < 2 || fieldValue.front() != '"' || fieldValue.back() != '"') {
                in.setstate(std::ios::failbit);
                return in;
            }
            data.key3 = fieldValue.substr(1, fieldValue.size() - 2);
            hasKey3 = true;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 0x" << std::hex << std::uppercase << data.key1
        << ":key2 #c(" << data.key2.real() << " " << data.key2.imag()
        << "):key3 \"" << data.key3 << "\":)";
    return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    
    const double modA = std::abs(a.key2);
    const double modB = std::abs(b.key2);
    if (modA != modB) {
        return modA < modB;
    }
    
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(data));
    
    std::sort(data.begin(), data.end(), compareDataStructs);
    
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
    
    return 0;
}