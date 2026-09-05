#ifndef CONSOLE_CONSOLE_H
#define CONSOLE_CONSOLE_H

#include "vault.h"

class Console {
public:
  explicit Console(Vault::Ptr vault);
  void Run();

private:
  auto ReadInputLine(const std::string& prompt) -> std::string&;
  void AddEntryCommand();
  void ListEntriesCommand();
  void AskForPasswordAndOpenVault();

  Vault::Ptr vault_;
};

#endif // CONSOLE_CONSOLE_H