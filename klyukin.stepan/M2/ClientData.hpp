#ifndef CLIENT_DATA_HPP
#define CLIENT_DATA_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "Circle.hpp"

namespace klyukin
{
  class ClientData
  {
  public:
    // ClientData(int v);
    int seed;
    std::unordered_map< std::string, Circle > circles;
    std::unordered_map< std::string, std::unordered_set< std::string >> sets;
  };
}

#endif
