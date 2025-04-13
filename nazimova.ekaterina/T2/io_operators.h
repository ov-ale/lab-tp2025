#ifndef IO_OPERATORS_H
#define IO_OPERATORS_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "data_struct.h"

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);

#endif
