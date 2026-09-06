#ifndef SRC_ENTRY_H
#define SRC_ENTRY_H

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

#endif  // SRC_ENTRY_H