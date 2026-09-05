#ifndef UTIL_PRINT_H
#define UTIL_PRINT_H

#include <iostream>

namespace util {

static void PrintSuccessMessage(const std::string& message) {
  std::cout << "[✓] " << message;
}

static void PrintErrorMessage(const std::string& message) {
  std::cout << "[✗] " << message;
}

static void PrintInfoMessage(const std::string& message) {
  std::cout << "[i] " << message;
}

static void PrintWarningMessage(const std::string& message) {
  std::cout << "[!] " << message;
}

static void PrintDebugMessage(const std::string& message) {
  std::cout << "[DEBUG] " << message;
}

static void PrintCommandHeader(const std::string& command_name) {
  std::cout << "\n--- " << command_name << " ---\n\n";
}

}  // namespace util

#endif  // UTIL_PRINT_H