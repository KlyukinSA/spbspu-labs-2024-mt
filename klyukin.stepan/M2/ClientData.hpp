#ifndef CLIENT_DATA_HPP
#define CLIENT_DATA_HPP

#include <vector>
#include <forward_list>
#include <iosfwd>

namespace klyukin
{
  class ClientData
  {
  public:
    ClientData(int v);
    int value;
  };
}

#endif
