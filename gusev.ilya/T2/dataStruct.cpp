#include "dataStruct.h"
#include <sstream>
#include <iomanip>
#include <iostream>

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
    std::ios::fmtflags flags = out.flags(); // Сохраняем текущие флаги форматирования
    out << "(:key1 " << std::scientific << std::setprecision(6) << data.key1
        << ":key2 " << data.key2
        << ":key3 \"" << data.key3 << "\":)";
    out.flags(flags); // Восстанавливаем флаги форматирования
    return out;
}
