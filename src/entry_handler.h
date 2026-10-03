#ifndef SRC_ENTRY_HANDLER_H
#define SRC_ENTRY_HANDLER_H

#include <vector>

#include "entry.h"

class EntryHandler {
 public:
  static auto GetEntries() -> std::vector<Entry::Ptr>;
  static auto GetEntryById(int entry_id) -> Entry::Ptr;
  static void AddEntry(const Entry& title, const int& user_id);
  static void ViewEntry(int entry_id);
  static void DeleteEntry(int entry_id);
  static void UpdateEntry(const Entry::Ptr& entry);

 private:
  static auto LoadEntriesFromFile() -> std::vector<Entry::Ptr>;
  static void SaveEntriesToFile();
};

#endif  // SRC_ENTRY_HANDLER_H