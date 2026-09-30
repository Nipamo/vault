#include "file_handler.h"

#include <stdexcept>

FileHandler::FileHandler(const std::filesystem::path& path)
    : file_{path.string()} {
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

  if (file_.peek() == std::fstream::traits_type::eof()) {
    return true;
  }
  return false;
}