#include "console.h"
#include "vault.h"
#include <cstdlib>
#include <iostream>

constexpr auto kCommandPrefix{"vault"};

Console::Console(Vault::Ptr vault) : vault_(vault) {}

void Console::AskForPasswordAndOpenVault() {
  if (vault_->IsLocked()) {
    std::cout << "Vault is locked.\n\n"
              << "Master password: ";
    do {
      std::string input_password;
      std::getline(std::cin, input_password);
      if (input_password == vault_->GetMasterPassword()) {
        vault_->Unlock();
        std::cout << "Vault unlocked!\n\n";
      } else {
        std::cout << "Wrong password! Try again: ";
      }
    } while (vault_->IsLocked());
  }
}

void Console::Run() {
  while (true) {
    AskForPasswordAndOpenVault();
  }
}
