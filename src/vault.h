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
  auto GetEntryById(const int& id) -> Entry*;
  void AddEntry(Entry& entry);

  void SetEntryService(const std::string& service);
  void SetEntryUsername(const std::string& username);
  void SetEntryPassword(const std::string& password);
  void SetEntryNote(const std::string& note);

 private:
  const std::string master_password_{"0000"};
  std::vector<Entry> entries_;
  bool is_locked_{true};
};

#endif  // SRC_VAULT_H