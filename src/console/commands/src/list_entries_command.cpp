#include "include/list_entries_command.h"

#include <iomanip>
#include <iostream>

#include "util/print.h"

static constexpr auto kCommandName{"list"};
static constexpr auto kCommandDescription{"List all entries"};
static constexpr auto kCommandHeader{"List Entries"};
static constexpr auto kMaxPrintedNoteLength{31U};

namespace {

void PrintTableHeader() {
  std::cout << std::left << std::setw(6) << "ID" << std::setw(24) << "Service"
            << std::setw(28) << "Username" << std::setw(16) << "Password"
            << std::setw(34) << "Note"
            << "\n";
  std::cout << std::string(108, '-') << "\n";
}

void PrintTableEntry(const Entry& entry) {
  std::string password_masked = std::string(entry.password.length(), '*');
  std::string note = entry.note;

  if (note.length() > kMaxPrintedNoteLength) {
    note = note.substr(0, kMaxPrintedNoteLength) + "...";
  }

  std::cout << std::left << std::setw(6) << entry.id << std::setw(24)
            << entry.service << std::setw(28) << entry.username << std::setw(16)
            << password_masked << std::setw(34) << note << "\n";
}

}  // namespace

ListEntriesCommand::ListEntriesCommand(Vault::Ptr vault)
    : Command(kCommandName, kCommandDescription, {}), vault_(vault) {}

void ListEntriesCommand::Execute() {
  const auto& entries = vault_->GetEntries();

  if (entries.empty()) {
    util::PrintInfoMessage("No entries found.\n\n");
    return;
  }

  util::PrintCommandHeader(kCommandHeader);

  PrintTableHeader();
  for (const auto& entry : entries) {
    PrintTableEntry(entry);
  }
  PrintEntryAmount();
}

void ListEntriesCommand::PrintEntryAmount() {
  const auto& entries = vault_->GetEntries();
  std::cout << "\n";
  std::string entry_label = entries.size() == 1 ? "entry" : "entries";
  std::ostringstream message_stream;
  message_stream << entries.size() << " " << entry_label << " found.\n\n";
  util::PrintInfoMessage(message_stream.str());
  std::cout << "\n";
}