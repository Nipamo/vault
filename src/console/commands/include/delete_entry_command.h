#ifndef CONSOLE_COMMANDS_DELETE_ENTRY_COMMAND_H
#define CONSOLE_COMMANDS_DELETE_ENTRY_COMMAND_H

#include "command.h"
#include "vault.h"

class DeleteEntryCommand : public Command {
 public:
  explicit DeleteEntryCommand(Vault::Ptr vault);
  void Execute() final;

 private:
  void DeleteEntryById();
  void DeleteEntryByService();
  void PrintAllEntriesWithService(const std::string& service);

  Vault::Ptr vault_;
};

#endif  // CONSOLE_COMMANDS_DELETE_ENTRY_COMMAND_H