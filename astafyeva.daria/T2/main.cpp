#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& data) {
    data.key1 = 0;
    data.key2 = 0;
    data.key3.clear();
    
    char ch;
    if (!(is >> std::ws >> ch) || ch != '(') {
        is.setstate(std::ios::failbit);
        return is;
    }
    
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    std::string keyPart;
    
    while (is >> std::ws >> ch && ch == ':') {
        std::string key;
        is >> key;
        
        if (key == "key1") {
            std::string value;
            is >> value;
            try {
                size_t pos;
                data.key1 = std::stoull(value, &pos, 8);
                if (pos != value.size()) throw std::exception();
                hasKey1 = true;
            } catch (...) {
                is.setstate(std::ios::failbit);
                return is;
            }
        } else if (key == "key2") {
            std::string value;
            is >> value;
            try {
                size_t pos;
                data.key2 = std::stoull(value, &pos, 16);
                if (pos != value.size()) throw std::exception();
                hasKey2 = true;
            } catch (...) {
                is.setstate(std::ios::failbit);
                return is;
            }
        } else if (key == "key3") {
            char quote;
            if (!(is >> quote) || quote != '"') {
                is.setstate(std::ios::failbit);
                return is;
            }
            std::getline(is, data.key3, '"');
            hasKey3 = true;
        } else {
            std::string dummy;
            std::getline(is, dummy, ':');
        }
        
        is >> ch;
        if (ch != ':') {
            is.putback(ch);
            break;
        }
    }
    
    if (!hasKey1 || !hasKey2 || !hasKey3 || !(is >> ch) || ch != ')') {
        is.setstate(std::ios::failbit);
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 0" << std::oct << data.key1 << "u11"
       << ":key2 0x" << std::hex << data.key2 << "u11"
       << ":key3 \"" << data.key3 << "\":)";
    return os;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}

int main() {
    std::vector<DataStruct> data;
    
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(data));
    
    std::sort(data.begin(), data.end(), compareDataStruct);
    
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
    
    return 0;
}