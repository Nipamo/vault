#include "console.h"
#include "vault.h"
#include <cstdlib>
#include <iostream>
#include <limits>

namespace console {

constexpr auto kCommandPrefix = "vault";

Console::Console(src::Vault::Ptr vault) : vault_ptr_(vault) { Run(); }

void Console::Run() {
  while (true) {
    std::string command;
    std::getline(std::cin, command);

    // Command muss mit "Vault" starten
    if (command != kCommandPrefix)
      return;

    // vault erstellen wenn nicht vorhanden
    if (vault_ptr_ == nullptr) {
      std::cout << "No vault found!\n\n"
                << "Create new vault? [y/n]: ";
      char yes_or_no;
      std::cin >> yes_or_no;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (yes_or_no == 'y') {
        CreateVault();
      } else {
        std::cout << "Quitting application!\n";
        exit(EXIT_SUCCESS);
      }
    }
  }
}

void Console::CreateVault() {
  std::cout << "Name: ";
  std::string vault_name;
  std::getline(std::cin, vault_name);

  vault_ptr_ = std::make_shared<src::Vault>(vault_name);
  std::cout << "Vault created successfully!\n\n";
}

} // namespace console