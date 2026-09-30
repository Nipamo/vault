#ifndef CONSOLE_FILE_HANDLER_H
#define CONSOLE_FILE_HANDLER_H

#include <filesystem>
#include <fstream>

class FileHandler {
 public:
  explicit FileHandler(const std::filesystem::path& path);
  ~FileHandler();

  auto GetFile() const -> std::fstream&;
  auto IsFileEmpty() const -> bool;

 private:
  mutable std::fstream file_;
};

#endif  // CONSOLE_FILE_HANDLER_H