#ifndef CONSOLE_CONSOLE_H
#define CONSOLE_CONSOLE_H

#include "vault.h"

class Console {
public:
  explicit Console(Vault::Ptr vault);
  void Run();

private:
  void AskForPasswordAndOpenVault();

  Vault::Ptr vault_;
};

#endif // CONSOLE_CONSOLE_H