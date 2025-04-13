#include "dataStruct.h"
#include <sstream>
#include <cctype>
#include <cmath>
#include <vector>

std::vector<std::string> splitKeyValueParts(const std::string &line) {
    std::vector<std::string> parts;
    std::string current;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        }

        if (c == ':' && !inQuotes) {
            parts.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }

    if (!current.empty()) {
        parts.push_back(current);
    }

    return parts;
}

bool parseDoubleLiteral(const std::string &s, double &value)
{
    if (s.empty())
        return false;
    size_t pos = 0;
    try
    {
        value = std::stod(s, &pos);
    }
    catch (...)
    {
        return false;
    }
    if (pos < s.size())
    {
        if (s.size() - pos != 1)
            return false;
        char suffix = tolower(s.back());
        if (suffix != 'd')
            return false;
    }
    return true;
}

bool parseHexLiteral(const std::string &s, unsigned long long &value)
{
    if (s.empty())
        return false;
    if (s.size() < 3)
        return false;
    if (s[0] != '0' || (tolower(s[1]) != 'x'))
        return false;

    try
    {
        value = std::stoull(s.substr(2), nullptr, 16);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool parseQuotedString(const std::string &s, std::string &value)
{
    size_t firstQuote = s.find('"');
    size_t lastQuote = s.rfind('"');
    if (firstQuote == std::string::npos || lastQuote == std::string::npos || firstQuote == lastQuote)
    {
        return false;
    }
    value = s.substr(firstQuote + 1, lastQuote - firstQuote - 1);
    return true;
}

std::istream &operator>>(std::istream &in, DataStruct &ds)
{
    std::string line;
    if (!std::getline(in, line))
        return in;

    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);

    if (line.size() < 4 || line.substr(0, 2) != "(:" || line.substr(line.size() - 2) != ":)")
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    line = line.substr(2, line.size() - 4);

    DataStruct temp;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    std::vector<std::string> parts = splitKeyValueParts(line);
    for (const auto &part : parts)
    {
        std::istringstream partStream(part);
        std::string key;
        partStream >> key;

        if (key == "key1")
        {
            std::string value;
            partStream >> value;
            if (!parseDoubleLiteral(value, temp.key1))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey1 = true;
        }
        else if (key == "key2")
        {
            std::string value;
            partStream >> value;
            if (!parseHexLiteral(value, temp.key2))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey2 = true;
        }
        else if (key == "key3")
        {
            std::string value;
            partStream >> std::ws;
            std::getline(partStream, value);
            if (!parseQuotedString(value, temp.key3))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey3 = true;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    ds = temp;
    return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &ds)
{
    out << "(:key1 " << std::fixed << std::setprecision(1) << ds.key1 << "d:key2 0x"
        << std::hex << std::uppercase << ds.key2 << ":key3 \"" << ds.key3 << "\":)";
    out << std::dec << std::nouppercase;
    return out;
}

bool compareDataStructs(const DataStruct &a, const DataStruct &b)
{
    if (a.key1 != b.key1)
        return a.key1 < b.key1;
    if (a.key2 != b.key2)
        return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}
