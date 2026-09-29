#include "file_handler.h"

FileHandler::FileHandler(const std::string& path) : file_{path} {
  if (!file_.is_open()) {
    throw std::runtime_error("Failed opening file!\n");
  }
}

FileHandler::~FileHandler() {
  if (file_.is_open()) {
    file_.close();
  }
}

auto FileHandler::GetFile() -> std::fstream& { return file_; }