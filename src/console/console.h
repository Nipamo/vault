#ifndef CONSOLE_CONSOLE_H
#define CONSOLE_CONSOLE_H

#include "vault.h"
#include <string>

namespace src::console {

using vault::Vault;

class Console {
public:
  Console(Vault::Ptr vault = nullptr);
  void Run();
  void PrintMessage(const std::string& message);
  void PrintMessageWithoutBreak(const std::string& message);

private:
  void CreateVault();
  auto ReadInputWithMessage(const std::string& message) -> std::string;

  Vault::Ptr vault_ptr_;
};
} // namespace src::console

#endif // CONSOLE_CONSOLE_H