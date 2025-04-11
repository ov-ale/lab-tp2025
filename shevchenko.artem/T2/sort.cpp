#include "sort.h"


bool nspace::compare(const DataStruct left, const DataStruct right)
{
    if (left.key1 < right.key1)
    {
        return true;
    }
    else if (left.key1 == right.key1)
    {
        if (left.key2.first < right.key2.first)
        {
            return true;
        }
        else if (left.key2.first == right.key2.first)
        {
            if (left.key2.second < right.key2.second)
            {
                return true;
            }
            else if (left.key2.second == right.key2.second)
            {
                if (left.key3.size() < right.key3.size())
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}

void nspace::sortDataVector(std::vector<DataStruct>& data)
{
    std::sort(data.begin(), data.end(), compare);
}