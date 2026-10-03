#ifndef SRC_USER_HANDLER_H
#define SRC_USER_HANDLER_H

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

struct UserInfo {
  int user_id;
  std::string username;
  std::string password;
};

class UserHandler {
 public:
  void CreateNewAccount(const std::string& username,
                        const std::string& password);
  static auto UsernameExists(const std::string& username) -> bool;
  static auto UserIdExists(const int& user_id) -> bool;
  static auto GetUserIdByUsername(const std::string& username) -> int;
  auto ValidatePassword(const std::string& username,
                        const std::string& password) -> bool;
  void ToJson(nlohmann::json& json, const UserInfo& user_info);
  static void FromJson(const nlohmann::json& json, UserInfo& user_info);

 private:
  static auto GetUserInfoFromFile(const std::string& username) -> UserInfo;
  static auto GetAllUsersFromFile() -> std::vector<UserInfo>;
  void WriteUserInfoToFile(const UserInfo& user_info);
};

#endif  // SRC_USER_HANDLER_H