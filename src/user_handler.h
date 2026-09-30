#ifndef SRC_USER_HANDLER_H
#define SRC_USER_HANDLER_H

#include <nlohmann/json_fwd.hpp>
#include <string>

class UserHandler {
 public:
  void CreateNewAccount(const std::string& username,
                        const std::string& password);
  auto UsernameExists(const std::string& username) -> bool;
  auto ValidatePassword(const std::string& username,
                        const std::string& password) -> bool;

 private:
  auto GetFileJson() -> nlohmann::json;
};

#endif  // SRC_USER_HANDLER_H