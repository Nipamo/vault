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
static constexpr auto kUsernameTag{"username"};
static constexpr auto kPasswordTag{"password"};

void UserHandler::CreateNewAccount(const std::string& username,
                                   const std::string& password) {
  FileHandler file_handler(kSavedDataPath);
  Json user_infos = Json::object();
  auto& stream = file_handler.GetFile();

  if (!file_handler.IsFileEmpty()) {
    stream >> user_infos;
  }

  stream.clear();
  stream.seekg(0, std::ios::beg);
  stream.seekp(0, std::ios::beg);

  user_infos[kUsernameTag] = username;
  user_infos[kPasswordTag] = password;

  file_handler.GetFile() << std::setw(2) << user_infos;
  stream.flush();

  util::PrintSuccessMessage("Created new account successfully!\n");
}

auto UserHandler::UsernameExists(const std::string& username) -> bool {
  Json user_infos = GetFileJson();

  if (user_infos.contains(kUsernameTag) &&
      user_infos[kUsernameTag] == username) {
    return true;
  }

  util::PrintWarningMessage("Username not found!\n");
  return false;
}

auto UserHandler::ValidatePassword(const std::string& username,
                                   const std::string& password) -> bool {
  Json user_infos = GetFileJson();
  if (!UsernameExists(username)) {
    return false;
  }

  if (user_infos.contains(kPasswordTag) &&
      user_infos[kPasswordTag] == password) {
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
    file_handler.GetFile() >> user_infos;
  }
  return user_infos;
}