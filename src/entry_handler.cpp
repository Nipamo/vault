#include "entry_handler.h"

#include <vault.h>

#include <nlohmann/json.hpp>
#include <vector>

#include "entry.h"
#include "file_handler.h"
#include "user_handler.h"
#include "util/print.h"

using Json = nlohmann::json;

static constexpr auto kEntriesTag{"entries"};

auto EntryHandler::GetEntries() -> std::vector<Entry::Ptr> {
  std::vector<Entry::Ptr> user_entries;
  auto all_entries = LoadEntriesFromFile();
  for (const auto& entry : all_entries) {
    if (entry->user_id == Vault::GetUserId()) {
      user_entries.push_back(entry);
    }
  }

  return user_entries;
}

auto EntryHandler::GetEntryById(int entry_id) -> Entry::Ptr {
  std::vector<Entry::Ptr> entries = LoadEntriesFromFile();
  for (auto& entry : entries) {
    if (entry->entry_id == entry_id && entry->user_id == Vault::GetUserId()) {
      return entry;
    }
  }
  return Entry::Ptr();
}

void EntryHandler::AddEntry(const Entry& entry, const int& user_id) {
  if (!entry.IsValid()) {
    throw std::invalid_argument("Invalid entry.");
  }

  if (!UserHandler::UserIdExists(user_id)) {
    throw std::invalid_argument("Invalid user ID.");
  }

  FileHandler file_handler;
  Json root = file_handler.GetFileJson();
  if (!root.contains(kEntriesTag) || !root[kEntriesTag].is_array()) {
    root[kEntriesTag] = Json::array();
  }

  auto entries = LoadEntriesFromFile();
  Entry new_entry = entry;
  new_entry.user_id = user_id;
  new_entry.entry_id = entries.empty() ? 1 : entries.back()->entry_id + 1;

  root[kEntriesTag].push_back(new_entry.ToJson());
  file_handler.SaveJson(root);
}

void EntryHandler::UpdateEntry(const Entry::Ptr& entry) {
  if (!entry->IsValid()) {
    throw std::invalid_argument("Invalid entry.");
  }

  if (entry->user_id != Vault::GetUserId()) {
    util::PrintErrorMessage("You do not have permission to update this entry.");
    return;
  }

  FileHandler file_handler;
  Json root = file_handler.GetFileJson();
  if (!root.contains(kEntriesTag) || !root[kEntriesTag].is_array()) {
    root[kEntriesTag] = Json::array();
  }

  bool found = false;
  for (auto& existing_entry_json : root[kEntriesTag]) {
    Entry existing_entry;
    existing_entry.FromJson(existing_entry_json);

    if (existing_entry.entry_id == entry->entry_id &&
        existing_entry.user_id == Vault::GetUserId()) {
      existing_entry = *entry;
      existing_entry_json = existing_entry.ToJson();
      found = true;
      break;
    }
  }

  if (!found) {
    throw std::invalid_argument("Entry not found.");
  }

  file_handler.SaveJson(root);
}

void EntryHandler::DeleteEntry(int entry_id) {
  FileHandler file_handler;
  Json root = file_handler.GetFileJson();
  if (!root.contains(kEntriesTag) || !root[kEntriesTag].is_array()) {
    root[kEntriesTag] = Json::array();
    return;
  }

  auto& entries = root[kEntriesTag];
  auto it = std::remove_if(entries.begin(), entries.end(),
                           [entry_id](const Json& json_entry) {
                             Entry entry;
                             entry.FromJson(json_entry);
                             return entry.entry_id == entry_id &&
                                    entry.user_id == Vault::GetUserId();
                           });

  if (it == entries.end()) {
    throw std::invalid_argument("Entry not found.");
  }

  entries.erase(it, entries.end());
  file_handler.SaveJson(root);
}

auto EntryHandler::LoadEntriesFromFile() -> std::vector<Entry::Ptr> {
  FileHandler file_handler;
  Json entries_json = file_handler.GetFileJson();
  std::vector<Entry::Ptr> entries;

  if (!entries_json.contains(kEntriesTag) ||
      !entries_json[kEntriesTag].is_array()) {
    return entries;
  }

  for (const auto& value : entries_json[kEntriesTag]) {
    Entry::Ptr entry = std::make_shared<Entry>();
    entry->FromJson(value);
    entries.push_back(entry);
  }

  return entries;
}

void EntryHandler::SaveEntriesToFile() {
  FileHandler file_handler;
  Json root = file_handler.GetFileJson();
  Json entries_array = Json::array();

  for (const auto& entry : LoadEntriesFromFile()) {
    entries_array.push_back(entry->ToJson());
  }

  root[kEntriesTag] = entries_array;
  file_handler.SaveJson(root);
}