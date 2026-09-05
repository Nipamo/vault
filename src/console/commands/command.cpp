#include "command.h"

#include <iostream>

void Command::Execute() {
  if (action_) {
    action_();
  } else {
    std::cerr << "No action defined for this command." << std::endl;
  }
}

auto Command::ReadInputLine(const std::string& prompt) -> std::string {
  std::string input_line;
  std::cout << prompt;
  std::getline(std::cin, input_line);
  return input_line;
}