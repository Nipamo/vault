#include "vault.h"
#include <string>

void Vault::Lock() { is_locked_ = true; }

void Vault::Unlock() { is_locked_ = false; }

auto Vault::IsLocked() const -> bool { return is_locked_; }

auto Vault::GetMasterPassword() const -> const std::string& {
  return master_password_;
}