#ifndef AREA_CALCULATION_HPP
#define AREA_CALCULATION_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "Circle.hpp"

namespace klyukin
{
  class AreaCalculation
  {
  public:
    AreaCalculation(const std::unordered_set< std::string >& set, int threads, int tries, const std::unordered_map< std::string, klyukin::Circle >& circles);
    AreaCalculation():
      resultFileDescriptor_(-1)
    {}
    double requestCalculationResult();
  private:
    int resultFileDescriptor_;
  };
}

#endif
