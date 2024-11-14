#include <iostream>

#include "Interpreter.hpp"

#include <sys/types.h>
#include <sys/wait.h> //

int main(int argc, const char* argv[])
{
  int seed = 0;
  if (argc > 1) {
    seed = std::atoi(argv[1]);
  }
  std::srand(seed);

  klyukin::Interpreter interpreter(std::cin, std::cout, klyukin::ClientData{seed, std::unordered_map< std::string, klyukin::Circle >(), std::unordered_map< std::string, std::unordered_set< std::string >>()});
  interpreter.runLoop("> ");
  while ((wait(NULL)) > 0); // this way, the father waits for all the child processes 
  return 0;
}
