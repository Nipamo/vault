#ifndef SRC_VAULT_H
#define SRC_VAULT_H

#include <memory>

class Vault {
public:
  using Ptr = std::shared_ptr<Vault>;

  void Lock();
  void Unlock();
  auto IsLocked() const -> bool;
  auto GetMasterPassword() const -> const std::string&;

private:
  const std::string master_password_{"0000"};
  bool is_locked_{true};
};

#endif // SRC_VAULT_H