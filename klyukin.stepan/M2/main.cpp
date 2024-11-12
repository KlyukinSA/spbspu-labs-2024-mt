#include <iostream>
#include <fstream>
#include "Interpreter.hpp"

int main(int argc, const char* argv[])
{
  int seed = 0;
  if (argc > 1) {
    seed = std::atoi(argv[1]);
  }
  std::srand(seed);

  klyukin::Interpreter interpreter(std::cin, std::cout, klyukin::ClientData{0});
  interpreter.runLoop("> ");
  return 0;
}
