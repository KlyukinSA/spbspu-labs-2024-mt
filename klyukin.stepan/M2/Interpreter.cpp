#include "Interpreter.hpp"
#include <iostream>
#include <string>
#include <limits>
#include "math.hpp"

klyukin::Interpreter::Interpreter(std::istream& in, std::ostream& out, ClientData&& data):
  data_(std::move(data)),
  in_(in),
  out_(out)
{}

void klyukin::Interpreter::createCircle()
{
  std::string name;
  int r, x, y;
  in_ >> name >> r >> x >> y;
  if (!in_ || r < 1)
  {
    out_ << "incorrect number\n";
    in_.clear();
    return;
  }
  if (data_.circles.find(name) != data_.circles.end()) {
    out_ << "circle exists\n";
    return;
  }
  data_.circles[name] = std::move(Circle{r, x, y});
}

void klyukin::Interpreter::createSet()
{
  std::string name;
  int setSize;
  in_ >> name >> setSize;
  if (!in_)
  {
    out_ << "incorrect number\n";
    in_.clear();
    return;
  }
  if (data_.sets.find(name) != data_.sets.end()) {
    out_ << "set exists\n";
    return;
  }
  std::string line;
  std::getline(in_, line);
  std::size_t pos1 = 1;
  std::size_t pos2 = line.find(' ', pos1);
  int count = 0;
  std::unordered_set< std::string > set;
  while (pos1 != std::string::npos && pos2 > pos1)
  {
    std::string circle = line.substr(pos1, pos2 - pos1);
    pos1 = pos2 + 1;
    pos2 = line.find(' ', pos1);
    count++;
    if (data_.circles.find(circle) == data_.circles.end()) {
      out_ << "circle not exists\n";
      return;
    }
    set.insert(circle);
  }
  if (count != setSize) {
    out_ << "incorrect set-size\n";
    return;
  }
  data_.sets[name] = std::move(set);
}

void klyukin::Interpreter::showCircle()
{
  std::string name;
  in_ >> name;
  auto circle = data_.circles.find(name);
  if (circle == data_.circles.end()) {
    out_ << "circle not exists\n";
    return;
  }
  out_ << circle->second;
}

void klyukin::Interpreter::showSet()
{
  std::string name;
  in_ >> name;
  auto set = data_.sets.find(name);
  if (set == data_.sets.end()) {
    out_ << "set not exists\n";
    return;
  }
  for (auto circle: set->second) {
    out_ << data_.circles.find(circle)->second;
  }
}

void klyukin::Interpreter::getCircleFrame()
{
  std::string name;
  in_ >> name;
  auto circle = data_.circles.find(name);
  if (circle == data_.circles.end()) {
    out_ << "circle not exists\n";
    return;
  }
  out_ << getBoundingRect(circle->second);
}

void klyukin::Interpreter::getSetFrame() // TODO repetition
{
  std::string name;
  in_ >> name;
  auto set = data_.sets.find(name);
  if (set == data_.sets.end()) {
    out_ << "set not exists\n";
    return;
  }
  out_ << getBoundingRect(set->second, data_.circles);
}



const std::map< std::string, void (klyukin::Interpreter::*)() >
  klyukin::Interpreter::commandsMap =
{
  {"circle", &Interpreter::createCircle},
  {"set", &Interpreter::createSet},
  {"show", &Interpreter::showCircle},
  {"showset", &Interpreter::showSet},
  {"frame", &Interpreter::getCircleFrame},
  {"frameset", &Interpreter::getSetFrame}
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
