#include "vault.h"
#include <string>

namespace src {

Vault::Vault(const std::string& name) : name_{std::move(name)} {}

auto Vault::getName() -> std::string { return name_; }
} // namespace src