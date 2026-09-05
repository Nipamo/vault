#ifndef CONSOLE_COMMANDS_I_COMMAND_H
#define CONSOLE_COMMANDS_I_COMMAND_H

#include <memory>
#include <string>

class ICommand {
 public:
  using Ptr = std::shared_ptr<ICommand>;

  ICommand() = default;
  ICommand(const std::string& name, const std::string& description)
      : name_(name), description_(description) {}
  virtual ~ICommand() = default;

  virtual void Execute() = 0;
  virtual auto description() const -> std::string { return description_; }

 private:
  std::string name_;
  std::string description_;
};

#endif  // CONSOLE_COMMANDS_I_COMMAND_H