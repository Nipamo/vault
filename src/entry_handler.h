#ifndef SRC_ENTRY_HANDLER_H
#define SRC_ENTRY_HANDLER_H

#include <vector>

#include "entry.h"

class EntryHandler {
 public:
  EntryHandler();
  static void AddEntry(const Entry& title, const int& user_id);
  static void ListEntries();
  static void ViewEntry(int entry_id);
  static void DeleteEntry(int entry_id);

 private:
  static auto LoadEntriesFromFile() -> std::vector<Entry>;
  static void SaveEntriesToFile();

  static std::vector<Entry> entries_;
};

#endif  // SRC_ENTRY_HANDLER_H