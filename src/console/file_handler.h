#ifndef CONSOLE_FILE_HANDLER_H
#define CONSOLE_FILE_HANDLER_H

#include <filesystem>
#include <fstream>
#include <nlohmann/json_fwd.hpp>

class FileHandler {
 public:
  FileHandler();
  explicit FileHandler(const std::filesystem::path& path);
  ~FileHandler();

  auto GetFile() const -> std::fstream&;
  auto GetFileJson() -> nlohmann::json;
  void SaveJson(const nlohmann::json& json);
  auto IsFileEmpty() const -> bool;

 private:
  std::filesystem::path file_path_;
  mutable std::fstream file_;
};

#endif  // CONSOLE_FILE_HANDLER_H