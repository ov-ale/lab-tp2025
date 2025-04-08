#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>

class StreamGuard {
  std::ios& stream;
  std::ios::fmtflags flags{};
public:
  StreamGuard(std::ios& stream);
  ~StreamGuard();
};

#endif