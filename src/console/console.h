#ifndef CONSOLE_CONSOLE_H
#define CONSOLE_CONSOLE_H

#include <map>

#include "i_command.h"
#include "vault.h"

class Console {
 public:
  explicit Console(Vault::Ptr vault);
  void Run();

 private:
  void InitCommands();
  void UnlockVault();
  void TryExecuteCommand(const int& index);
  auto ValidatePassword(const std::string& password) -> bool;
  void PrintMenu();

  Vault::Ptr vault_;
  std::map<int, ICommand::Ptr> command_map_;
};

#endif  // CONSOLE_CONSOLE_H