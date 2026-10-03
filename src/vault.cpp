#include "vault.h"

#include <entry_handler.h>

#include <stdexcept>
#include <string>
#include <vector>

int Vault::user_id_{0};

void Vault::Lock() { is_locked_ = true; }

void Vault::Unlock() { is_locked_ = false; }

auto Vault::IsLocked() const -> bool { return is_locked_; }

auto Vault::GetMasterPassword() const -> const std::string& {
  return master_password_;
}

void Vault::SetUserId(const int user_id) { user_id_ = user_id; }

auto Vault::GetUserId() -> int { return user_id_; }