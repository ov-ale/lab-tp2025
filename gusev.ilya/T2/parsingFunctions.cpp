#include "dataStruct.h"
#include <sstream>
#include <cctype>

bool parseScientificDouble(const std::string& str, double& value) {
    std::istringstream iss(str);
    iss >> value;
    return !iss.fail();
}

bool parseLongLong(const std::string& str, long long& value) {
    std::istringstream iss(str);

    if (str.length() > 2 && str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X") {
        iss >> std::hex >> value;
    }
    else if (str.length() > 2 && str.substr(0, 2) == "0b" || str.substr(0, 2) == "0B") {
        value = std::stoll(str.substr(2), nullptr, 2);
        return true;
    }
    else if (str.length() > 1 && str.front() == '0') {
        iss >> std::oct >> value;
    }
    else {
        iss >> std::dec >> value;
    }

    return !iss.fail();
}
