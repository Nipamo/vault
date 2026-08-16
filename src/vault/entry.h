#ifndef ENTRY_ENTRY_H
#define ENTRY_ENTRY_H

#include <ostream>
#include <string>

namespace src::vault {

struct Entry {
  std::string name;
  std::string user_name;
  std::string password;
  std::string notes;

  friend std::ostream& operator<<(std::ostream& os, const Entry& entry);
};

inline std::ostream& operator<<(std::ostream& os, const Entry& entry) {
  os << "> Name: " << entry.name << '\n';
  os << "> Username: " << entry.user_name << '\n';
  os << "> Password: " << entry.password << '\n';
  os << "> Notes: " << entry.notes << '\n';

  return os;
}

} // namespace src::vault

#endif // ENTRY_ENTRY_H