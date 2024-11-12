#include "BoundingRect.hpp"
#include <iostream>

std::ostream& klyukin::operator<<(std::ostream& out, const BoundingRect& rect)
{
  return out << '(' << rect.x1 << ' ' << rect.y1 << ") (" << rect.x2 << ' ' << rect.y2 << ")\n";
}
