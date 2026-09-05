#include <cstdlib>
#include <iostream>

#include "console.h"
#include "vault.h"

int main() {
  Vault::Ptr vault = std::make_shared<Vault>();
  Console console_(vault);

  std::cout << "----------------------------------------\n"
            << "             PASSWORD VAULT\n"
            << "----------------------------------------\n\n";

  console_.Run();
}