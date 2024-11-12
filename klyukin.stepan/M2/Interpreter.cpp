#include "Interpreter.hpp"
#include <iostream>
#include <string>
#include <limits>

klyukin::Interpreter::Interpreter(std::istream& in, std::ostream& out, ClientData&& data):
  data_(std::move(data)),
  in_(in),
  out_(out)
{}

void klyukin::Interpreter::increase()
{
  std::size_t n;
  in_ >> n;
  if (in_)
  {
    data_.value += n;
  }
  else
  {
    out_ << "give nubmer\n";
    in_.clear();
  }
}

void klyukin::Interpreter::getCurrentValue()
{
  out_ << data_.value << "\n";
}

const std::map< std::string, void (klyukin::Interpreter::*)() >
  klyukin::Interpreter::commandsMap =
{
  {"inc", &Interpreter::increase},
  {"get", &Interpreter::getCurrentValue}
};

void klyukin::Interpreter::runLoop(const char* prompt)
{
  const bool invite = true;
  std::string str;
  if (invite)
  {
    out_ << prompt;
  }
  in_ >> str;
  while (!in_.eof())
  {
    try
    {
      if (commandsMap.find(str) != commandsMap.end())
      {
        (this->*(commandsMap.find(str)->second))();
      }
      else
      {
        in_.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        throw std::logic_error("no such command");
      }
    }
    catch(const std::exception& e)
    {
      out_ << e.what() << '\n';
    }
    if (invite)
    {
      out_ << prompt;
    }
    in_ >> str;
  }
  if (invite)
  {
    out_ << '\n';
  }
}
