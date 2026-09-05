#ifndef CONSOLE_COMMANDS_LIST_ENTRIES_COMMAND_H
#define CONSOLE_COMMANDS_LIST_ENTRIES_COMMAND_H

#include "command.h"
#include "vault.h"

class ListEntriesCommand : public Command {
 public:
  explicit ListEntriesCommand(Vault::Ptr vault);
  void Execute() final;

 private:
  void PrintEntryAmount();

  Vault::Ptr vault_;
};

#endif  // CONSOLE_COMMANDS_LIST_ENTRIES_COMMAND_H