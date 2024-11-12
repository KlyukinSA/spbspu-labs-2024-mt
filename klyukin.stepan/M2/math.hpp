#ifndef MATH_HPP
#define MATH_HPP

#include <unordered_map>
#include <unordered_set>
#include "BoundingRect.hpp"
#include "Circle.hpp"

namespace klyukin
{
  BoundingRect getBoundingRect(const Circle& circle);
  BoundingRect getBoundingRect(const std::unordered_set< std::string >& set, std::unordered_map< std::string, Circle > circles);
}

#endif
