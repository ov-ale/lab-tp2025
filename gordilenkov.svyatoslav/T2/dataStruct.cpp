#include "dataStruct.h"
#include <iomanip>
#include <regex>
#include <sstream>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    if (!std::getline(in, line))
        return in;

    std::smatch match;
    std::regex full_re(R"(\(:.*:\))");
    if (!std::regex_match(line, full_re))
        return in;

    std::regex key1_re(R"(:key1\s+0[0-7]+:)");
    std::regex key2_re(R"(:key2\s+#c\(\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s+([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*\):)");
    std::regex key3_re(R"key(:key3\s+"([^"]*)":)key");

    if (!std::regex_search(line, match, key1_re))
        return in;
    std::string key1_str = match.str();
    size_t pos = key1_str.find("0");
    data.key1 = std::stoull(key1_str.substr(pos), nullptr, 8);

    if (!std::regex_search(line, match, key2_re))
        return in;
    double real = std::stod(match[1].str());
    double imag = std::stod(match[2].str());
    data.key2 = std::complex<double>(real, imag);

    if (!std::regex_search(line, match, key3_re))
        return in;
    data.key3 = match[1].str();

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 " << std::oct << data.key1 << std::dec
        << ":key2 #c(" << std::fixed << std::setprecision(1)
        << data.key2.real() << " " << data.key2.imag() << ")"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

// Компаратор
bool compareData(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;

    double absA = std::abs(a.key2);
    double absB = std::abs(b.key2);
    if (absA != absB) return absA < absB;

    return a.key3.length() < b.key3.length();
}
