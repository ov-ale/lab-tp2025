#include "dataStruct.h"
#include "streamGuard.h"
#include <stdexcept>

unsigned long long parseOctal(const std::string& str) {
    unsigned long long value = 0;
    std::istringstream iss(str);
    if (!(iss >> std::oct >> value) || !iss.eof()) {
        throw std::invalid_argument("Invalid octal number");
    }
    return value;
}

std::complex<double> parseComplex(const std::string& str) {
    double real = 0.0, imag = 0.0;
    std::istringstream iss(str);
    if (!(iss >> real >> imag) || !iss.eof()) {
        throw std::invalid_argument("Invalid complex number");
    }
    return { real, imag };
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    if (!std::getline(in, line) || line.empty()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    try {
        size_t k1 = line.find(":key1");
        size_t k2 = line.find(":key2");
        size_t k3 = line.find(":key3");

        if (k1 == std::string::npos || k2 == std::string::npos || k3 == std::string::npos) {
            throw std::invalid_argument("Missing key marker");
        }

        size_t start = line.find(" ", k1) + 1;
        size_t end = line.find(":", start);
        if (start == std::string::npos + 1 || end == std::string::npos) {
            throw std::invalid_argument("Invalid key1 format");
        }
        std::string key1_str = line.substr(start, end - start);
        data.key1 = parseOctal(key1_str);

        start = line.find("#c(", k2) + 3;
        end = line.find(")", start);
        if (start == std::string::npos + 3 || end == std::string::npos) {
            throw std::invalid_argument("Invalid key2 format");
        }
        std::string complexStr = line.substr(start, end - start);
        data.key2 = parseComplex(complexStr);

        start = line.find("\"", k3) + 1;
        end = line.find("\"", start);
        if (start == std::string::npos + 1 || end == std::string::npos) {
            throw std::invalid_argument("Invalid key3 format");
        }
        data.key3 = line.substr(start, end - start);
    }
    catch (...) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    StreamGuard guard(out);
    out << "(:key1 0" << std::oct << data.key1
        << ":key2 #c(" << std::fixed << std::setprecision(1)
        << data.key2.real() << " " << data.key2.imag()
        << "):key3 \"" << data.key3 << "\":)";
    return out;
}

bool compareData(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1)
        return lhs.key1 < rhs.key1;
    if (std::norm(lhs.key2) != std::norm(rhs.key2))
        return std::norm(lhs.key2) < std::norm(rhs.key2);
    return lhs.key3.length() < rhs.key3.length();
}
