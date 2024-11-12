#include "Circle.hpp"
#include <iostream>

std::ostream& klyukin::operator<<(std::ostream& out, const Circle& circle)
{
  return out << circle.r << " (" << circle.x << ' ' << circle.y << ")\n";
}
