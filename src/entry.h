#ifndef SRC_ENTRY_H
#define SRC_ENTRY_H

#include <nlohmann/json.hpp>
#include <ostream>
#include <string>

static constexpr auto kUserIdTag{"user_id"};
static constexpr auto kIdTag{"id"};
static constexpr auto kServiceTag{"service"};
static constexpr auto kUsernameTag{"username"};
static constexpr auto kPasswordTag{"password"};
static constexpr auto kNoteTag{"note"};

// The entry needs to contain the Service and at least one additional attribute.
// If not, it would not be neccessary to store it
struct Entry {
  using Ptr = std::shared_ptr<Entry>;

  int entry_id;
  int user_id;
  std::string service;
  std::string username;
  std::string password;
  std::string note;

  auto IsValid() const -> bool {
    if (service.empty()) {
      return false;
    }

    const auto has_additional_attribute =
        !username.empty() || !password.empty() || !note.empty();

    return has_additional_attribute;
  }

  auto ToJson() const -> nlohmann::json {
    nlohmann::json json;
    json[kUserIdTag] = user_id;
    json[kIdTag] = entry_id;
    json[kServiceTag] = service;
    json[kUsernameTag] = username;
    json[kPasswordTag] = password;
    json[kNoteTag] = note;
    return json;
  }

  auto FromJson(const nlohmann::json& json) -> void {
    user_id = json.value(kUserIdTag, 0);
    entry_id = json.value(kIdTag, 0);
    service = json.value(kServiceTag, "");
    username = json.value(kUsernameTag, "");
    password = json.value(kPasswordTag, "");
    note = json.value(kNoteTag, "");
  }

  auto operator==(const Entry& other) const {
    return entry_id == other.entry_id && user_id == other.user_id &&
           service == other.service && username == other.username &&
           password == other.password && note == other.note;
  }
};

inline std::ostream& operator<<(std::ostream& output, const Entry& entry) {
  auto password_masked = std::string(entry.password.length(), '*');
  return output << "ID: " << entry.entry_id << "\n"
                << "Service: " << entry.service << "\n"
                << "Username: " << entry.username << "\n"
                << "Password: " << password_masked << "\n"
                << "Note: " << entry.note;
}

#endif  // SRC_ENTRY_H