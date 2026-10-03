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

  static void SetUserId(const int user_id);
  static auto GetUserId() -> int;

 private:
  const std::string master_password_{"0000"};
  bool is_locked_{true};
  static int user_id_;
};

#endif  // SRC_VAULT_H