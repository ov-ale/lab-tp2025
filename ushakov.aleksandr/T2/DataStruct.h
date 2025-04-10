#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <complex> 
#include <cmath>
namespace nspace
{
   struct DataStruct
   {
      long long key1;
      std::complex<double> key2;
      std::string key3;
   
   };
   struct DelimiterIO
   {
      char expr;
   };
   
   struct LongLongIO
   {
      long long& ref;
   };
   
   struct ComplexIO
   {
      std::complex<double>& ref;
   };
   
   struct StringIO
   {
      std::string& ref;
   };
   
   class iofmtguard
   {
      public:
      iofmtguard(std::basic_ios<char>& s) :
      s_(s),
      width_(s.width()),
      fill_(s.fill()),
      precision_(s.precision()),
      fmt_(s.flags())
      {}
      ~iofmtguard()
      {
         s_.width(width_);
         s_.fill(fill_);
         s_.precision(precision_);
         s_.flags(fmt_);
      }
      private:
      std::basic_ios< char >& s_;
      std::streamsize width_;
      char fill_;
      std::streamsize precision_;
      std::basic_ios< char >::fmtflags fmt_;
   };
   //Проверка наличия определенного символа-разделителя
   std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
   {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c;
    in >> c;
    if (in && (c != dest.expr))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
   }
   //Запись строки
   std::istream& operator>>(std::istream& in, StringIO&& dest)
   {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
   }
   //Запись числа типа long long
   std::istream& operator>>(std::istream& in, LongLongIO&& dest)
    {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> dest.ref;
    char first, second;
    if (in >> first >> second) 
    {
      if (tolower(first) != 'l' && tolower(second) != 'l') 
      {
          in.setstate(std::ios::failbit);
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  //Запись комплексного числа
  std::istream& operator>>(std::istream& in, ComplexIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    double real = 0.0, imag = 0.0;
    in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('} 
    >> real >> imag >> DelimiterIO{')'};
    if (in) 
    {
      dest.ref = std::complex<double>(real, imag);
    }
    return in;
  }
  //Проверка DataStruct
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using ll = LongLongIO;
      using str = StringIO;
      using cmp = ComplexIO;
      bool hasKey1 = false;
      bool hasKey2 = false;
      bool hasKey3 = false;
      in >> sep{'('};
      while(!(hasKey1 && hasKey2 && hasKey3))
      {
        std::string currentKey;
        in >> sep{':'};
        in >> currentKey;
        if(currentKey == "key1")
        {
          in >> ll{ input.key1 };
          hasKey1 = true;
        }
        else if(currentKey == "key2")
        {
          in >> cmp{input.key2};
          hasKey2 = true;
        }
        else if(currentKey == "key3")
        {
          in >> str{input.key3};
          hasKey3 = true;
        }
        else
        {
          break;
        }
      }
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
  //Вывод DataStruct
  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:";
    out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "ll: ";
    out << "key2 #c(" << src.key2.real() << " " << src.key2.imag() << "): ";
    out << "key3 \"" << src.key3 << "\"";
    out << " :)";
    return out;
  }
  //Собственный компаратор
  bool comparator(const DataStruct& first, const DataStruct& second)
  {
    if (first.key1 != second.key1) return first.key1 < second.key1;
            
    if(first.key2 != second.key2)
    {
      return std::abs(first.key2) < std::abs(second.key2);
    }
    
    return first.key3.length() < second.key3.length();
  }
   
}
