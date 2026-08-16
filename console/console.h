#ifndef CONSOLE_CONSOLE_H
#define CONSOLE_CONSOLE_H

#include "vault.h"

namespace console {

class Console {
public:
  Console(src::Vault::Ptr vault = nullptr);
  void Run();

private:
  void CreateVault();

  src::Vault::Ptr vault_ptr_;
};
} // namespace console

#endif // CONSOLE_CONSOLE_H