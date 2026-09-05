#ifndef CONSOLE_COMMANDS_COMMAND_H
#define CONSOLE_COMMANDS_COMMAND_H

#include <functional>
#include <string>

#include "i_command.h"

class Command : public ICommand {
 public:
  using Function = std::function<void()>;

  Command() = default;
  Command(const std::string& name, const std::string& description,
          Function action)
      : ICommand(name, description), action_(action) {}

  void Execute() override;
  static auto ReadInputLine(const std::string& prompt) -> std::string;

 private:
  Function action_;
};

#endif  // CONSOLE_COMMANDS_COMMAND_H