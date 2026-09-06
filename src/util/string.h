#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <cstddef>
#include <string>

namespace util {

static void CutFrontSpaces(std::string& string) {
  size_t start = string.find_first_not_of(' ');

  if (start == std::string::npos) {
    string.clear();
  } else {
    string.erase(0, start);
  }
}

}  // namespace util

#endif  // UTIL_STRING_H