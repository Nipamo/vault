#include "vault.h"
#include <string>
#include <vector>

namespace src::vault {

auto Vault::GetName() -> std::string { return name_; }

void Vault::AddEntry(const Entry& entry) { entries_.push_back(entry); }

auto Vault::GetEntries() -> std::vector<Entry> { return entries_; }

} // namespace src::vault