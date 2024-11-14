#include "math.hpp"
#include <algorithm>
#include <limits>
#include <string>
#include <thread>
#include <numeric>

#include <iostream> //

klyukin::BoundingRect klyukin::getBoundingRect(const klyukin::Circle& circle)
{
  return BoundingRect{circle.x - circle.r, circle.y - circle.r, circle.x + circle.r, circle.y + circle.r};
}

namespace klyukin {
  static BoundingRect initBound()
  {
    return BoundingRect{std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
  }

  static void updateBound(BoundingRect& res, const Circle& circle)
  {
    res.x1 = std::min(res.x1, circle.x - circle.r);
    res.x2 = std::max(res.x2, circle.x + circle.r);
    res.y1 = std::min(res.y1, circle.y - circle.r);
    res.y2 = std::max(res.y2, circle.y + circle.r);
  }
}

klyukin::BoundingRect klyukin::getBoundingRect(const std::unordered_set< std::string >& set, const std::unordered_map< std::string, Circle >& circles)
{
  klyukin::BoundingRect res = initBound();
  for (auto circleName: set) {
    updateBound(res, circles.find(circleName)->second);
  }
  return res;
}

namespace klyukin {
  static BoundingRect getBoundingRect(std::vector< Circle >::iterator begin, std::vector< Circle >::iterator end)
  {
    BoundingRect res = initBound();
    for (auto iterator = begin; iterator != end; ++iterator) {
      updateBound(res, *iterator);
    }
    return res;
  }

  static void countHits(std::vector< double >::iterator begin, std::vector< double >::iterator end, std::vector< Circle >::iterator dataBegin, std::vector< Circle >::iterator dataEnd, std::vector< int >::iterator res) // TODO template Iterator
  {
    for (auto pointIterator = begin; pointIterator != end; ++pointIterator) {
      const double x = *pointIterator;
      ++pointIterator;
      const double y = *pointIterator;
      for (auto circleIterator = dataBegin; circleIterator != dataEnd; ++circleIterator) {
        const double dx = circleIterator->x - x;
        const double dy = circleIterator->y - y;
        // std::cout << dx * dx + dy * dy << '\n';
        if (dx * dx + dy * dy < circleIterator->r * circleIterator->r) {
          *res += 1;
          break;
        }
      }
    }
  }

  static int getArea(const BoundingRect& rect)
  {
    // std::cout << rect.x2  << ' ' << rect.x1  << '_' << rect.y2 << ' ' << rect.y1 << '\n';
    return (rect.x2 - rect.x1) * (rect.y2 - rect.y1);
  }
}

double klyukin::calculateArea(std::vector< klyukin::Circle >::iterator begin, std::vector< klyukin::Circle >::iterator end, int threadsCount, int tries) // TODO template Iterator
{
  klyukin::BoundingRect rect = getBoundingRect(begin, end);

  std::vector< double > coordinates;
  const int dimentionsCount = 2;
  coordinates.reserve(tries * dimentionsCount);
  for (int i = 0; i < tries; i++) {
    coordinates.push_back((double(rand()) / RAND_MAX) * (rect.x2 - rect.x1) + rect.x1);
    coordinates.push_back((double(rand()) / RAND_MAX) * (rect.y2 - rect.y1) + rect.y1);
  }

  std::vector< std::thread > threads;
  threads.reserve(threadsCount);
  std::vector< int > results(threadsCount, 0);
  const int triesPerThread = tries / threadsCount;
  for (int i = 0; i < threadsCount - 1; i++) {
    threads.emplace_back(countHits, coordinates.begin() + i * triesPerThread * dimentionsCount, coordinates.begin() + (i + 1) * triesPerThread * dimentionsCount, begin, end, results.begin() + i);
  }
  countHits(coordinates.begin() + (threadsCount - 1) * triesPerThread * dimentionsCount, coordinates.end(), begin, end, results.begin() + (threadsCount - 1));
  for (auto && th: threads) {
    th.join();
  }
  const double prob = double(std::accumulate(results.cbegin(), results.cend(), 0)) / tries;
  return getArea(rect) * prob;
}
