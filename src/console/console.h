#ifndef CONSOLE_CONSOLE_H
#define CONSOLE_CONSOLE_H

#include <map>

#include "file_handler.h"
#include "i_command.h"
#include "user_handler.h"
#include "vault.h"

class Console {
 public:
  explicit Console(Vault::Ptr vault);
  void Run();

 private:
  void InitCommands();
  auto UnlockVault() -> bool;
  void TryExecuteCommand(const int& index);
  auto ValidatePassword(const std::string& password) -> bool;
  void PrintMenu();
  auto CreateNewAccount() -> bool;

  Vault::Ptr vault_;
  UserHandler user_handler_;
  std::map<int, ICommand::Ptr> command_map_;
};

#endif  // CONSOLE_CONSOLE_H