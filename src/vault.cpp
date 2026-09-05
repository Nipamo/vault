#include "vault.h"

#include <string>

void Vault::Lock() { is_locked_ = true; }

void Vault::Unlock() { is_locked_ = false; }

auto Vault::IsLocked() const -> bool { return is_locked_; }

auto Vault::GetMasterPassword() const -> const std::string& {
  return master_password_;
}

auto Vault::GetEntries() const -> const std::vector<Entry>& { return entries_; }

void Vault::AddEntry(Entry& entry) {
  entry.id = entries_.size() + 1;
  entries_.push_back(entry);
}