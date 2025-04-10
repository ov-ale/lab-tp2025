#ifndef SORT_H
#define SORT_H
#include "nspace.h"
#include <vector>
using nspace::Data;


void sort(std::vector< Data >& obj) {
    Data forSwap;
    for (size_t i = 0; i < obj.size() - 1; i++) {
        for (size_t j = obj.size() - 1; j > i; j--) {
            if ((obj[j].key1 < obj[j - 1].key1) ||
                (obj[j].key1 == obj[j - 1].key1 &&
                    obj[j].key2 < obj[j - 1].key2) ||
                (obj[j].key1 == obj[j - 1].key1 &&
                    obj[j].key2 == obj[j - 1].key2 &&
                    obj[j].key3.size() < obj[j - 1].key3.size())) {
                forSwap = obj[j];
                obj[j] = obj[j - 1];
                obj[j - 1] = forSwap;
            }
        }
    }
}

#endif // !SORT_H
