#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iosfwd>
#include <memory>
#include <map>
#include "ClientData.hpp"

namespace klyukin
{
  class Interpreter
  {
    public:
      static const std::map< std::string, void (Interpreter::*)() > commandsMap;
      Interpreter(std::istream& in, std::ostream& out, ClientData&& data);
      void runLoop(const char* prompt);

      void createCircle();
      void createSet();
      void showCircle();
      void showSet();
      void printCircle(const Circle& circle);

    private:
      ClientData data_;
      std::istream& in_;
      std::ostream& out_;
  };
}

#endif
