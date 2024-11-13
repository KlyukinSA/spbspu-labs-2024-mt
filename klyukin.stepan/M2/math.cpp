#include "math.hpp"
#include <algorithm>
#include <limits>
#include <string>

klyukin::BoundingRect klyukin::getBoundingRect(const klyukin::Circle& circle)
{
  return BoundingRect{circle.x - circle.r, circle.y - circle.r, circle.x + circle.r, circle.y + circle.r};
}

klyukin::BoundingRect klyukin::getBoundingRect(const std::unordered_set< std::string >& set, const std::unordered_map< std::string, Circle >& circles)
{
  klyukin::BoundingRect res{std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
  for (auto circleName: set) {
    auto circle = circles.find(circleName)->second;
    res.x1 = std::min(res.x1, circle.x - circle.r);
    res.x2 = std::max(res.x2, circle.x + circle.r);
    res.y1 = std::min(res.y1, circle.y - circle.r);
    res.y2 = std::max(res.y2, circle.y + circle.r);
  }
  return res;
}
