#include <iostream>

#include "Interpreter.hpp"

int main(int argc, const char* argv[])
{
  int seed = 0;
  if (argc > 1) {
    seed = std::atoi(argv[1]);
  }
  std::srand(seed);

  klyukin::Interpreter interpreter(std::cin, std::cout, klyukin::ClientData{seed, std::unordered_map< std::string, klyukin::Circle >(), std::unordered_map< std::string, std::unordered_set< std::string >>()});
  interpreter.runLoop("> ");
  return 0;
}
