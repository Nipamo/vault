#ifndef SRC_ENTRY_H
#define SRC_ENTRY_H

#include <string>

struct Entry {
  int id;
  std::string service;
  std::string username;
  std::string password;
  std::string notes;
};

#endif // SRC_ENTRY_H