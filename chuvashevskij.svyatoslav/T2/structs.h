#ifndef STRUCTS_H
#define STRUCTS_H
#include <string>
#include <iostream>
#include <vector>

namespace structs
{
    struct Data
    {
        double key1;
        std::string key2;
        std::string key3;
        bool isCorrect = true;
        bool operator<(const Data& other) const
        {
            if (key1 != other.key1)
            {
                return key1 < other.key1;
            }
            if (key2 != other.key2)
            {
                return key2 < other.key2;
            }
            return key3.size() < other.key3.size();
        }
    };

    struct Separator
    {
        char sep;
    };

    struct SDouble
    {
        double& ref;
    };

    struct Mantissa
    {
        double& ref;
    };

    struct Order
    {
        int& ref;
    };

    struct Label
    {
        std::string& ref;
    };

    struct ULLBin
    {
        std::string& ref;
    };

    struct String
    {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, Separator&& dest);
    std::istream& operator>>(std::istream& in, SDouble&& dest);
    std::istream& operator>>(std::istream& in, Mantissa&& dest);
    std::istream& operator>>(std::istream& in, Order&& dest);
    std::istream& operator>>(std::istream& in, Label&& dest);
    std::istream& operator>>(std::istream& in, ULLBin&& dest);
    std::istream& operator>>(std::istream& in, String&& dest);
    std::istream& operator>>(std::istream& in, Data& dest);
    std::ostream& operator<<(std::ostream& out, const Data& dest);
    void makeCorrect(std::vector<Data>& data);
}


#endif // !STRUCTS_H
