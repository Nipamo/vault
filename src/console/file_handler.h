#ifndef CONSOLE_FILE_HANDLER_H
#define CONSOLE_FILE_HANDLER_H

#include <fstream>

class FileHandler {
 public:
  explicit FileHandler(const std::string& path);
  ~FileHandler();

  auto GetFile() -> std::fstream&;

 private:
  std::fstream file_;
};

#endif  // CONSOLE_FILE_HANDLER_H