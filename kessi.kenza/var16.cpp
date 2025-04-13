#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <utility>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iterator>

// Variant 16: key1 is double (DBL LIT), key2 is rational, key3 is string
struct DataStruct {
    double key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

// Removes whitespace from beginning and end of a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Parses a rational number of format (:N val:D val:) into a pair<long long, unsigned long long>
bool parseRational(const std::string& str, std::pair<long long, unsigned long long>& rat) {
    std::istringstream iss(str);
    std::string token;
    long long n = 0;
    unsigned long long d = 1;
    bool hasN = false, hasD = false;

    while (iss >> token) {
        if (token == ":N") {
            if (!(iss >> n)) return false;
            hasN = true;
        }
        else if (token == ":D") {
            if (!(iss >> d)) return false;
            hasD = true;
        }
    }

    if (hasN && hasD && d != 0) {
        rat = { n, d };
        return true;
    }
    return false;
}

// Overload input stream operator to read DataStruct from formatted input line
std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    if (!std::getline(in, line)) return in;

    line = trim(line);
    if (line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Remove surrounding parentheses
    line = line.substr(1, line.size() - 2);
    std::istringstream iss(line);
    std::string token;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    while (iss >> token) {
        if (token == ":key1") {
            std::string val;
            if (!(iss >> val)) break;

            // Remove 'd' or 'D' from end and convert to double
            if (!val.empty() && (val.back() == 'd' || val.back() == 'D')) {
                val.pop_back();
                try {
                    data.key1 = std::stod(val);
                    hasKey1 = true;
                }
                catch (...) {
                    break;
                }
            }
        }
        else if (token == ":key2") {
            // Read rational as a single string until closing ')'
            std::string raw, full;
            if (!(iss >> raw)) break;
            full += raw;
            while (raw.back() != ')') {
                if (!(iss >> raw)) break;
                full += ' ' + raw;
            }

            // Remove outer parentheses and parse
            if (full.front() == '(' && full.back() == ')') {
                full = full.substr(1, full.size() - 2);
                if (parseRational(full, data.key2)) {
                    hasKey2 = true;
                }
            }
        }
        else if (token == ":key3") {
            // Read string with quotes, handle space inside string
            std::string val;
            if (!(iss >> val)) break;

            if (val.front() == '"') {
                std::ostringstream full;
                full << val;
                while (val.back() != '"' || val.size() == 1) {
                    if (!(iss >> val)) break;
                    full << ' ' << val;
                }
                val = full.str();

                // Remove quotes
                if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                    data.key3 = val.substr(1, val.size() - 2);
                    hasKey3 = true;
                }
            }
        }
    }

    // If any field is missing, mark input as invalid
    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

// Overload output stream operator to format DataStruct
std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 << "d"
        << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

// Comparator function for sorting DataStruct
bool compare(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;

    // Compare rational numbers by cross-multiplying
    long long left = a.key2.first * static_cast<long long>(b.key2.second);
    long long right = b.key2.first * static_cast<long long>(a.key2.second);
    if (left != right) return left < right;

    // If both key1 and key2 are equal, compare key3 string length
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;

    // Read input using iterators (bad lines will be ignored)
    std::copy(std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    // Sort using custom comparator
    std::sort(data.begin(), data.end(), compare);

    // Output all sorted DataStruct objects
    std::copy(data.begin(), data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
