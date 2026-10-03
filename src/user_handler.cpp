#include "user_handler.h"

#include <filesystem>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "file_handler.h"
#include "util/print.h"

using Json = nlohmann::json;
using Path = std::filesystem::path;

static const auto kSavedDataPath =
    Path(__FILE__).parent_path().parent_path() / "user.json";
static constexpr auto kUsersTag{"users"};
static constexpr auto kIdTag{"user_id"};
static constexpr auto kUsernameTag{"username"};
static constexpr auto kPasswordTag{"password"};

void UserHandler::CreateNewAccount(const std::string& username,
                                   const std::string& password) {
  if (username.empty()) {
    util::PrintWarningMessage("Username cannot be empty!\n");
    return;
  }

  std::vector<UserInfo> users = GetAllUsersFromFile();
  for (const auto& user : users) {
    if (user.username == username) {
      util::PrintWarningMessage("Username already exists!\n");
      return;
    }
  }

  UserInfo new_user;
  new_user.user_id = users.empty() ? 1 : users.back().user_id + 1;
  new_user.username = username;
  new_user.password = password;

  WriteUserInfoToFile(new_user);
  util::PrintSuccessMessage("Created new account successfully!\n");
}

auto UserHandler::UsernameExists(const std::string& username) -> bool {
  return GetUserInfoFromFile(username).username == username;
}

auto UserHandler::ValidatePassword(const std::string& username,
                                   const std::string& password) -> bool {
  const auto user_info = GetUserInfoFromFile(username);

  if (user_info.username != username) {
    return false;
  }

  if (user_info.password == password) {
    return true;
  }

  util::PrintWarningMessage("Incorrect password!\n");
  return false;
}

auto UserHandler::GetFileJson() -> Json {
  FileHandler file_handler(kSavedDataPath);
  Json user_infos;

  if (file_handler.IsFileEmpty()) {
    user_infos = Json::object();
  } else {
    file_handler.GetFile().seekg(0);
    file_handler.GetFile() >> user_infos;
  }
  return user_infos;
}

auto UserHandler::GetUserInfoFromFile(const std::string& username) -> UserInfo {
  std::vector<UserInfo> users = GetAllUsersFromFile();
  for (const auto& user_info : users) {
    if (user_info.username == username) {
      return user_info;
    }
  }

  return {0, "", ""};
}

auto UserHandler::GetAllUsersFromFile() -> std::vector<UserInfo> {
  Json user_infos = GetFileJson();
  std::vector<UserInfo> users;

  if (!user_infos.contains(kUsersTag) || !user_infos[kUsersTag].is_array()) {
    return users;
  }

  for (const auto& value : user_infos[kUsersTag]) {
    UserInfo user_info;
    FromJson(value, user_info);
    users.push_back(user_info);
  }
  return users;
}

void UserHandler::WriteUserInfoToFile(const UserInfo& user_info) {
  Json user_infos = GetFileJson();
  if (!user_infos.contains(kUsersTag) || !user_infos[kUsersTag].is_array()) {
    user_infos[kUsersTag] = Json::array();
  }

  Json new_user_info;
  ToJson(new_user_info, user_info);
  user_infos[kUsersTag].push_back(new_user_info);

  std::ofstream output_file(kSavedDataPath, std::ios::out | std::ios::trunc);
  if (!output_file.is_open()) {
    throw std::runtime_error("Failed opening file for writing!\n");
  }

  output_file << std::setw(2) << user_infos << '\n';
  output_file.flush();
}

void UserHandler::ToJson(Json& json, const UserInfo& user_info) {
  json = Json::object();
  json[kIdTag] = user_info.user_id;
  json[kUsernameTag] = user_info.username;
  json[kPasswordTag] = user_info.password;
}

void UserHandler::FromJson(const Json& json, UserInfo& user_info) {
  if (json.contains(kIdTag)) {
    user_info.user_id = json[kIdTag].get<int>();
  }
  if (json.contains(kUsernameTag)) {
    user_info.username = json[kUsernameTag].get<std::string>();
  }
  if (json.contains(kPasswordTag)) {
    user_info.password = json[kPasswordTag].get<std::string>();
  }
}