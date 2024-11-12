#ifndef BOUNDING_RECT_HPP
#define BOUNDING_RECT_HPP

#include <iosfwd>

namespace klyukin
{
  class BoundingRect
  {
  public:
    int x1;
    int y1;
    int x2;
    int y2;
  };
  std::ostream& operator<<(std::ostream&, const BoundingRect&);
}

#endif
