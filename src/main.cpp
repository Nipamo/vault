#include "vault.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <ostream>
#include <string>

namespace src {

auto CreateVault() {
  std::cout << "Name: ";
  std::string vault_name;
  std::getline(std::cin, vault_name);

  Vault::Ptr vault = std::make_shared<Vault>(vault_name);
  std::cout << "Vault created successfully!\n\n";

  return vault;
}

int main() {
  Vault::Ptr vault_;

  std::cout << "Welcome to your vaults!\n";

  while (true) {
    std::string command;
    std::cin >> command;

    if (command == "vault") {
      if (vault_ == nullptr) {
        std::cout << "No vault found!\n\n"
                  << "Create new vault? [y/n]: ";
        char yes_or_no;
        std::cin >> yes_or_no;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (yes_or_no == 'y') {
          vault_ = CreateVault();
        } else {
          std::cout << "Quitting application!\n";
          return EXIT_SUCCESS;
        }
      } else {
        std::cout << "Your vault: " << vault_->getName() << '\n';
      }
    }
  }
}

} // namespace src