#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iosfwd>

namespace klyukin
{
  class Circle
  {
  public:
    int r;
    int x;
    int y;
  };
  std::ostream& operator<<(std::ostream&, const Circle&);
}

#endif
