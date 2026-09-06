#ifndef CONSOLE_COMMANDS_EDIT_ENTRY_COMMAND_H
#define CONSOLE_COMMANDS_EDIT_ENTRY_COMMAND_H

#include "command.h"
#include "vault.h"

class EditEntryCommand : public Command {
 public:
  explicit EditEntryCommand(Vault::Ptr vault);
  void Execute() final;

 private:
  void UpdateEntryService(Entry* entry);
  void UpdateEntryUsername(Entry* entry);
  void UpdateEntryPassword(Entry* entry);
  void UpdateEntryNote(Entry* entry);

  Vault::Ptr vault_;
};

#endif  // CONSOLE_COMMANDS_EDIT_ENTRY_COMMAND_H