#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include "StreamGuard.h"
#include <sstream>
#include <iomanip>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

bool parseULLLit(const std::string& str, unsigned long long& value) {
    size_t suffix_pos = str.find("ull");
    if(suffix_pos == std::string::npos) {
        suffix_pos = str.find("ULL");
        if(suffix_pos == std::string::npos) {
            return false;
        }
    }

    try {
        value = std::stoull(str.substr(0, suffix_pos));
        return true;
    }
    catch(...) {
        return false;
    }
}

bool parseULLOct(const std::string& str, unsigned long long& value) {
    if(str.empty() || str[0] != '0') {
        return false;
    }

    for(char c : str) {
        if(c < '0' || c > '7') {
            return false;
        }
    }

    try {
        value = std::stoull(str, nullptr, 8);
        return true;
    }

    catch(...) {
        return false;
    }
}

std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string line;
    if(!std::getline(is, line)) {
        return is;
    }

    size_t start = line.find("(:");
    size_t end = line.find(":)");
    if(start == std::string::npos || end == std::string::npos) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::string content = line.substr(start + 2, end - start - 2);
    std::istringstream iss(content);
    std::string part;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;


    while(std::getline(iss, part, ':')) {
        std::istringstream part_ss(part);
        std::string key;
        part_ss >> key;

        if(key == "key1") {
            std::string val;
            part_ss >> val;
            if(!parseULLLit(val, ds.key1)) {
                is.setstate(std::ios::failbit);
                return is;
            }
            hasKey1 = true;
        }

        else if(key == "key2") {
            std::string val;
            part_ss >> val;
            if(!parseULLOct(val, ds.key2)) {
                is.setstate(std::ios::failbit);
                return is;
            }
            hasKey2 = true;
        }

        else if(key == "key3") {
            part_ss >> std::ws;
            if(part_ss.peek() != '"') {
                is.setstate(std::ios::failbit);
                return is;
            }
            part_ss.get();
            std::getline(part_ss, ds.key3, '"');
            hasKey3 = true;
        }
    }

    if(!hasKey1 || !hasKey2 || !hasKey3) {
        is.setstate(std::ios::failbit);
        return is;
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    StreamGuard guard(os);

    os << "(:key1 " << ds.key1 << "ull:key2 ";

    if(ds.key2 != 0) {
        os << '0';
    }

    os << std::oct << ds.key2 << std::dec;
    os << ":key3 \"" << ds.key3 << "\":)";
    return os;
}

bool compare(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.size() < b.key3.size();
}

#endif
