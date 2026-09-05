#ifndef CONSOLE_COMMAND_H
#define CONSOLE_COMMAND_H

#include <functional>
#include <string>

class Command {
 public:
 private:
  std::string name_;
  std::string description_;
  std::function<void()> action_;
};

#endif  // CONSOLE_COMMAND_H