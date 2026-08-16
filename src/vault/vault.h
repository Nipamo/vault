#ifndef SRC_VAULT_H
#define SRC_VAULT_H

#include "entry.h"
#include <memory>
#include <vector>

namespace src::vault {

class Vault {
public:
  using Ptr = std::shared_ptr<Vault>;

  void AddEntry(const Entry& entry);
  auto GetEntries() -> std::vector<Entry>;
  auto GetName() -> std::string;

private:
  std::string name_;
  std::vector<Entry> entries_;
};

} // namespace src::vault

#endif // SRC_VAULT_H