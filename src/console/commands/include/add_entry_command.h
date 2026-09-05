#ifndef CONSOLE_COMMANDS_ADD_ENTRY_COMMAND_H
#define CONSOLE_COMMANDS_ADD_ENTRY_COMMAND_H

#include "command.h"
#include "vault.h"

class AddEntryCommand : public Command {
 public:
  explicit AddEntryCommand(Vault::Ptr vault);
  void Execute() final;

 private:
  Vault::Ptr vault_;
};

#endif  // CONSOLE_COMMANDS_ADD_ENTRY_COMMAND_H