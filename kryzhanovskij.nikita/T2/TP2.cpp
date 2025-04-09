#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <complex>
#include <cctype>
#include <regex>

using namespace std;

struct DataStruct {
    unsigned long long key1;
    complex<double> key2;
    string key3;
};

// Объявления функций
bool parseBinaryULL(const string& s, unsigned long long& value);
bool parseComplex(const string& s, complex<double>& value);
bool parseDataStruct(const string& line, DataStruct& data);
bool compareDataStruct(const DataStruct& a, const DataStruct& b);
istream& operator>>(istream& in, DataStruct& data);
ostream& operator<<(ostream& out, const DataStruct& data);

int main() {
    vector<DataStruct> dataVector;

    // Чтение данных с помощью итераторов и алгоритмов STL
    copy(
        istream_iterator<DataStruct>(cin),
        istream_iterator<DataStruct>(),
        back_inserter(dataVector)
    );

    // Сортировка данных
    sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    // Вывод результатов
    copy(
        dataVector.begin(),
        dataVector.end(),
        ostream_iterator<DataStruct>(cout, "\n")
    );

    return 0;
}

// Реализации функций

bool parseBinaryULL(const string& s, unsigned long long& value) {
    if (s.size() < 2 || (s[0] != '0' && s[1] != 'b' && s[0] != '0' && s[1] != 'B')) {
        return false;
    }

    try {
        value = stoull(s.substr(2), nullptr, 2);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool parseComplex(const string& s, complex<double>& value) {
    if (s.size() < 4 || s[0] != '#' || s[1] != 'c' || s[2] != '(') {
        return false;
    }

    size_t space_pos = s.find(' ', 3);
    if (space_pos == string::npos) {
        return false;
    }

    try {
        double real = stod(s.substr(3, space_pos - 3));
        double imag = stod(s.substr(space_pos + 1, s.size() - space_pos - 2));
        value = complex<double>(real, imag);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool parseDataStruct(const string& line, DataStruct& data) {
    regex field_regex(":key(\\d+)\\s([^:]+):");
    sregex_iterator it(line.begin(), line.end(), field_regex);
    sregex_iterator end;

    bool has_key1 = false, has_key2 = false, has_key3 = false;

    for (; it != end; ++it) {
        smatch match = *it;
        string key_num = match[1].str();
        string value = match[2].str();

        if (key_num == "1") {
            if (parseBinaryULL(value, data.key1)) {
                has_key1 = true;
            }
            else {
                return false;
            }
        }
        else if (key_num == "2") {
            if (parseComplex(value, data.key2)) {
                has_key2 = true;
            }
            else {
                return false;
            }
        }
        else if (key_num == "3") {
            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                data.key3 = value.substr(1, value.size() - 2);
                has_key3 = true;
            }
            else {
                return false;
            }
        }
    }

    return has_key1 && has_key2 && has_key3;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;

    double a_mag = abs(a.key2);
    double b_mag = abs(b.key2);
    if (a_mag != b_mag) return a_mag < b_mag;

    return a.key3.length() < b.key3.length();
}

istream& operator>>(istream& in, DataStruct& data) {
    string line;
    if (getline(in, line)) {
        if (line.empty() || !parseDataStruct(line, data)) {
            in.setstate(ios::failbit);
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const DataStruct& data) {
    out << "(:key1 0b";

    // Вывод key1 в двоичном формате
    if (data.key1 == 0) {
        out << "0";
    }
    else {
        string binary;
        unsigned long long n = data.key1;
        while (n > 0) {
            binary = (n % 2 ? "1" : "0") + binary;
            n /= 2;
        }
        out << binary;
    }

    // Вывод key2 в комплексном формате
    out << ":key2 #c(" << data.key2.real() << " " << data.key2.imag() << ")";

    // Вывод key3 в строковом формате
    out << ":key3 \"" << data.key3 << "\":)";

    return out;
}