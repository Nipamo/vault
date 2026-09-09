#ifndef CONSOLE_COMMANDS_SEARCH_ENTRY_COMMAND_H
#define CONSOLE_COMMANDS_SEARCH_ENTRY_COMMAND_H

#include "command.h"
#include "vault.h"

class SearchEntryCommand : public Command {
 public:
  explicit SearchEntryCommand(Vault::Ptr vault);
  void Execute() final;

 private:
  void PrintEntryAmount();

  Vault::Ptr vault_;
};

#endif  // CONSOLE_COMMANDS_SEARCH_ENTRY_COMMAND_H