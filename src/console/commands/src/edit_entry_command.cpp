#include "include/edit_entry_command.h"

#include "entry.h"
#include "util/print.h"
#include "util/string.h"
#include "vault.h"

static constexpr auto kCommandName{"edit"};
static constexpr auto kCommandDescription{"Edit an existing entry (by ID)"};
static constexpr auto kCommandHeader{"Edit Entry"};

EditEntryCommand::EditEntryCommand(Vault::Ptr vault)
    : Command(kCommandName, kCommandDescription), vault_(vault) {}

void EditEntryCommand::Execute() {
  util::PrintCommandHeader(kCommandHeader);

  try {
    std::string input_id = ReadInputLine("Select an entry (ID): ");
    int selected_id = std::stoi(input_id);
    Entry* selected_entry = vault_->GetEntryById(selected_id);
    Entry original_entry = *selected_entry;

    util::PrintInfoMessage(
        "Service and one additional attribute needs to contain "
        "information\n\n");

    UpdateEntryService(selected_entry);
    UpdateEntryUsername(selected_entry);
    UpdateEntryPassword(selected_entry);
    UpdateEntryNote(selected_entry);

    if (!selected_entry->IsValid()) {
      *selected_entry = original_entry;
      util::PrintErrorMessage(
          "Invalid entry. Service and at least one additional attribute "
          "must contain information. Changes were discarded.\n");
      return;
    }

    if (*selected_entry == original_entry) {
      util::PrintInfoMessage("Nothing to change!\n\n");
    } else {
      util::PrintSuccessMessage("Updated entry successfully!\n\n");
    }
  } catch (const std::invalid_argument&) {
    util::PrintErrorMessage("Invalid input. Please enter a valid entry ID.\n");
  } catch (const std::out_of_range&) {
    util::PrintErrorMessage(
        "Input out of range. Please enter a valid entry ID.\n");
  }
}

void EditEntryCommand::UpdateEntryService(Entry* entry) {
  std::string service;
  std::cout << "Service: " << entry->service << "\n";
  std::cout << "New service (empty keeps the current value): ";
  std::getline(std::cin, service);
  util::CutFrontSpaces(service);
  if (!service.empty()) {
    entry->service = service;
  }
}

void EditEntryCommand::UpdateEntryUsername(Entry* entry) {
  std::string username;
  std::cout << "Username: " << entry->username << "\n";
  std::cout << "New username (empty keeps the current value): ";
  std::getline(std::cin, username);
  util::CutFrontSpaces(username);
  if (!username.empty()) {
    entry->username = username;
  }
}

void EditEntryCommand::UpdateEntryPassword(Entry* entry) {
  std::string password;
  std::cout << "Password: " << entry->password << "\n";
  std::cout << "New password (empty keeps the current value): ";
  std::getline(std::cin, password);
  util::CutFrontSpaces(password);
  if (!password.empty()) {
    entry->password = password;
  }
}

void EditEntryCommand::UpdateEntryNote(Entry* entry) {
  std::string note;
  std::cout << "Note: " << entry->note << "\n";
  std::cout << "New note (empty keeps the current value): ";
  std::getline(std::cin, note);
  util::CutFrontSpaces(note);
  if (!note.empty()) {
    entry->note = note;
  }
}
