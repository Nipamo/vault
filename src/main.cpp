#include <cstdlib>

#include "console.h"
#include "vault.h"

int main() {
  Vault::Ptr vault = std::make_shared<Vault>();
  Console console_(vault);
  console_.Run();
}