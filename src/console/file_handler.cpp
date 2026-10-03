#include "file_handler.h"

#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <stdexcept>

using Json = nlohmann::json;
using Path = std::filesystem::path;

static const auto kDefaultDataPath =
    Path(__FILE__).parent_path().parent_path().parent_path() / "user.json";

FileHandler::FileHandler() : FileHandler(kDefaultDataPath) {}

FileHandler::FileHandler(const std::filesystem::path& path)
    : file_path_{path}, file_{path.string(), std::ios::in | std::ios::out} {
  if (!file_.is_open()) {
    throw std::runtime_error("Failed opening file!\n");
  }
}

FileHandler::~FileHandler() {
  if (file_.is_open()) {
    file_.close();
  }
}

auto FileHandler::GetFile() const -> std::fstream& { return file_; }

auto FileHandler::IsFileEmpty() const -> bool {
  if (!file_.is_open()) {
    return true;
  }

  file_.clear();
  file_.seekg(0, std::ios::end);
  const auto file_size = file_.tellg();
  if (file_size <= 0) {
    return true;
  }

  file_.seekg(0);
  return false;
}

auto FileHandler::GetFileJson() -> Json {
  Json data;

  if (IsFileEmpty()) {
    data = Json::object();
    return data;
  }

  file_.clear();
  file_.seekg(0);
  file_ >> data;
  file_.clear();
  file_.seekg(0);
  return data;
}

void FileHandler::SaveJson(const Json& json) {
  file_.close();

  std::ofstream output_file(file_path_, std::ios::out | std::ios::trunc);
  if (!output_file.is_open()) {
    throw std::runtime_error("Failed opening file for writing!\n");
  }

  output_file << std::setw(2) << json << '\n';
  output_file.flush();
  output_file.close();

  file_.open(file_path_.string(), std::ios::in | std::ios::out);
  if (!file_.is_open()) {
    throw std::runtime_error("Failed reopening file after writing!\n");
  }
}