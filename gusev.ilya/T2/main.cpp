#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

bool parseScientificDouble(const std::string& str, double& value) {
    std::istringstream iss(str);
    iss >> value;
    return !iss.fail();
}

bool parseLongLong(const std::string& str, long long& value) {
    std::istringstream iss(str);
    iss >> value;
    return !iss.fail();
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    DataStruct temp;
    std::string line;

    if (!std::getline(in, line) || line.empty()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    line = line.substr(1, line.size() - 2);
    std::istringstream iss(line);
    std::string token;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    while (std::getline(iss, token, ':')) {
        if (token.empty()) continue;

        std::istringstream tokenStream(token);
        std::string key;
        tokenStream >> key;

        if (key == "key1") {
            std::string value;
            tokenStream >> value;
            if (!parseScientificDouble(value, temp.key1)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey1 = true;
        }
        else if (key == "key2") {
            std::string value;
            tokenStream >> value;
            if (!parseLongLong(value, temp.key2)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey2 = true;
        }
        else if (key == "key3") {
            std::string value;
            std::getline(tokenStream >> std::ws, value);
            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.size() - 2);
            }
            temp.key3 = value;
            hasKey3 = true;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    data = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 " << std::scientific << std::setprecision(6) << data.key1
        << ":key2 " << data.key2
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> dataVector;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector)
    );

    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    std::copy(
        dataVector.begin(),
        dataVector.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
