#ifndef UNIQUE_RECORD_H
#define UNIQUE_RECORD_H

#include <string>
#include <iostream>

struct Record {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& is, Record& rec);
std::ostream& operator<<(std::ostream& os, const Record& rec);

#endif
