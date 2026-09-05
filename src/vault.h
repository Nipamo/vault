#ifndef SRC_VAULT_H
#define SRC_VAULT_H

#include <memory>
#include <vector>

#include "entry.h"

class Vault {
 public:
  using Ptr = std::shared_ptr<Vault>;

  void Lock();
  void Unlock();
  auto IsLocked() const -> bool;
  auto GetMasterPassword() const -> const std::string&;
  auto GetEntries() const -> const std::vector<Entry>&;
  void AddEntry(Entry& entry);

 private:
  const std::string master_password_{"0000"};
  std::vector<Entry> entries_;
  bool is_locked_{true};
};

#endif  // SRC_VAULT_H