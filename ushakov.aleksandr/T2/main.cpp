#include "DataStruct.h"
int main()
{
  using nspace::DataStruct;
  std::vector<DataStruct> data;
  /* ДЛЯ ВВОДА:
  (:key1 898LL: key2 #c(5.5 8.0): key3 "T2":)
  (:key1 8LL: key2 #c(5.5 8.0): key3 "Hello World":)
  (:key1 8ll: key2 #c(5.5 8.0): key3 "I love TP":)
  (:key1 8LL: key2 #c(5.75 4): key3 "I love TP":)*/
  while (!std::cin.eof()) 
  {
    if (!std::cin) 
    {
        std::cin.clear();
    }

    std::copy(
      std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(data));
  }   
  
std::sort(data.begin(), data.end(), nspace::comparator);
std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}