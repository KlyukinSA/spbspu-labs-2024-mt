#ifndef MATH_HPP
#define MATH_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "BoundingRect.hpp"
#include "Circle.hpp"

namespace klyukin
{
  BoundingRect getBoundingRect(const Circle& circle);
  BoundingRect getBoundingRect(const std::unordered_set< std::string >& set, const std::unordered_map< std::string, Circle >& circles);
  double calculateArea(std::vector< Circle >::iterator, std::vector< Circle >::iterator, int, int);
}

#endif
