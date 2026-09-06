#ifndef SRC_ENTRY_H
#define SRC_ENTRY_H

#include <ostream>
#include <string>

// The entry needs to contain the Service and at least one additional attribute.
// If not, it would not be neccessary to store it
struct Entry {
  int id;
  std::string service;
  std::string username;
  std::string password;
  std::string note;

  auto IsValid() -> bool {
    if (service.empty()) {
      return false;
    }

    const auto has_additional_attribute =
        !username.empty() || !password.empty() || !note.empty();

    return has_additional_attribute;
  }

  auto operator==(const Entry& other) const {
    return id == other.id && service == other.service &&
           username == other.username && password == other.password &&
           note == other.note;
  }
};

inline std::ostream& operator<<(std::ostream& output, const Entry& entry) {
  auto password_masked = std::string(entry.password.length(), '*');
  return output << "ID: " << entry.id << "\n"
                << "Service: " << entry.service << "\n"
                << "Username: " << entry.username << "\n"
                << "Password: " << password_masked << "\n"
                << "Note: " << entry.note;
}

#endif  // SRC_ENTRY_H