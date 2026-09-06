#include "include/add_entry_command.h"

#include "entry.h"
#include "util/print.h"

static constexpr auto kCommandName{"add"};
static constexpr auto kCommandDescription{"Add a new entry"};
static constexpr auto kCommandHeader{"Add Entry"};

namespace {

auto CreateEntryFromInput() {
  std::string service = Command::ReadInputLine("Service: ");
  std::string username = Command::ReadInputLine("Username: ");
  std::string password = Command::ReadInputLine("Password: ");
  std::string note = Command::ReadInputLine("Note: ");

  Entry new_entry = {.service = service,
                     .username = username,
                     .password = password,
                     .note = note};

  return new_entry;
}

}  // namespace

AddEntryCommand::AddEntryCommand(Vault::Ptr vault)
    : Command(kCommandName, kCommandDescription, {}), vault_(vault) {}

void AddEntryCommand::Execute() {
  util::PrintCommandHeader(kCommandHeader);

  Entry new_entry;
  new_entry = CreateEntryFromInput();

  if (!new_entry.IsValid()) {
    util::PrintErrorMessage(
        "Invalid entry. Service and at least one additional attribute "
        "must contain information.\n\n");
    return;
  }

  vault_->AddEntry(new_entry);

  util::PrintSuccessMessage("Entry added successfully!\n\n");
}