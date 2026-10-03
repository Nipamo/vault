#include "entry_handler.h"

#include <nlohmann/json.hpp>
#include <vector>

#include "entry.h"
#include "file_handler.h"
#include "user_handler.h"

using Json = nlohmann::json;

static constexpr auto kEntriesTag{"entries"};
std::vector<Entry> EntryHandler::entries_;

EntryHandler::EntryHandler() { entries_ = LoadEntriesFromFile(); }

void EntryHandler::AddEntry(const Entry& entry, const int& user_id) {
  if (!entry.IsValid()) {
    throw std::invalid_argument("Invalid entry.");
  }

  if (!UserHandler::UserIdExists(user_id)) {
    throw std::invalid_argument("Invalid user ID.");
  }

  Entry new_entry = entry;
  new_entry.user_id = user_id;
  new_entry.entry_id = entries_.empty() ? 1 : entries_.back().entry_id + 1;
  entries_.push_back(new_entry);
  SaveEntriesToFile();
}

void EntryHandler::ListEntries() {}

void EntryHandler::ViewEntry(int entry_id) {}

void EntryHandler::DeleteEntry(int entry_id) {}

auto EntryHandler::LoadEntriesFromFile() -> std::vector<Entry> {
  FileHandler file_handler;
  Json entries_json = file_handler.GetFileJson();
  std::vector<Entry> entries;

  if (!entries_json.contains(kEntriesTag) ||
      !entries_json[kEntriesTag].is_array()) {
    return entries;
  }

  for (const auto& value : entries_json[kEntriesTag]) {
    Entry entry;
    entry.FromJson(value);
    entries.push_back(entry);
  }

  return entries;
}

void EntryHandler::SaveEntriesToFile() {
  FileHandler file_handler;
  Json entries_json = file_handler.GetFileJson();

  if (!entries_json.contains(kEntriesTag) ||
      !entries_json[kEntriesTag].is_array()) {
    entries_json[kEntriesTag] = Json::array();
  }

  for (const auto& entry : entries_) {
    Json entry_json = entry.ToJson();
    entries_json[kEntriesTag].push_back(entry_json);
  }

  file_handler.SaveJson(entries_json);
}