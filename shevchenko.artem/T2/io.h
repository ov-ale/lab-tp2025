#ifndef IO_H
#define IO_H

#include "dataStruct.h"
#include <iostream>
#include <string>
#include <tuple>

namespace nspace
{
    struct DelimiterIO // Для чтения разделителей
    { 
        char exp; 
    };

    struct DBLLITIO // Для чтения типа Double (key 1)
    { 
        double& ref; 
    };

    // Для чтения рациональных чисел (key 2)
    struct LLIO
    {
        long long& ref;
    };

    struct ULLIO
    {
        unsigned long long& ref;
    };
    
    struct StringIO // Для чтения строк (key 3)
    {
        std::string& ref; 
    };
    
    struct LabelIO // Для проверки меток
    {
        std::string exp;
    }; 


    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);        // Оператор ввода для DelimiterIO
    std::istream& operator>>(std::istream& in, DBLLITIO&& dest);           // Оператор ввода для DBL LIT
    std::istream& operator>>(std::istream& in, LLIO&& dest);               // Оператор ввода для Long Long
    std::istream& operator>>(std::istream& in, ULLIO&& dest);              // Оператор ввода для Unsigned Long Long
    std::istream& operator>>(std::istream& in, StringIO&& dest);           // Оператор ввода для string
    std::istream& operator>>(std::istream& in, DataStruct& dest);         // Оператор ввода для DataStruct
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);   // Оператор для вывода DataStruct
}

#endif