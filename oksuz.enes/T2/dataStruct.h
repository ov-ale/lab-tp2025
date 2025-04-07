#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iostream>

struct dataStruct {
    double key1;
    char key2;
    std::string key3;
    bool invalid = false;
};

std::istream& operator>>(std::istream& in, dataStruct& ds);
std::ostream& operator<<(std::ostream& out, const dataStruct& ds);

#endif