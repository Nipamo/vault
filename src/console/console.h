#ifndef CONSOLE_CONSOLE_H
#define CONSOLE_CONSOLE_H

#include <functional>
#include <map>

#include "vault.h"

struct Command {
  std::string name_;
  std::string description_;
  std::function<void()> action_;
};

class Console {
 public:
  explicit Console(Vault::Ptr vault);
  void Run();

 private:
  void PrintMenu();

  void CreateAddEntryCommand();
  void CreateListEntriesCommand();
  void CreateMenuCommand();
  void CreateExitCommand();

  void AskForPasswordAndOpenVault();
  void AddEntryCommand();
  void ListEntriesCommand();
  auto ReadInputLine(const std::string& prompt) -> std::string&;

  Vault::Ptr vault_;
  int command_index_{0};
  std::map<int, Command> command_map_;
};

#endif  // CONSOLE_CONSOLE_H