#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

struct Data {
  double key1{};
  char key2{};
  std::string key3{};
};

std::istream& operator>>(std::istream& stream, Data& data);
std::ostream& operator<<(std::ostream& stream, const Data& data);

#endif