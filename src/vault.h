#ifndef SRC_VAULT_H
#define SRC_VAULT_H

#include <memory>

namespace src {

class Vault {
public:
  using Ptr = std::shared_ptr<Vault>;

  explicit Vault(const std::string& name);

  auto getName() -> std::string;

private:
  std::string name_;
};

} // namespace src

#endif // SRC_VAULT_H