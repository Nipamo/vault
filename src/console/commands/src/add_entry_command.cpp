#include "include/add_entry_command.h"

#include <user_handler.h>

#include "entry.h"
#include "entry_handler.h"
#include "util/print.h"

static constexpr auto kCommandName{"add"};
static constexpr auto kCommandDescription{"Add a new entry"};
static constexpr auto kCommandHeader{"Add Entry"};

namespace {

auto CreateEntryFromInput() {
  auto service = Command::ReadInputLine("Service: ");
  auto username = Command::ReadInputLine("Username: ");
  auto password = Command::ReadInputLine("Password: ");
  auto note = Command::ReadInputLine("Note: ");

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

  auto user_id = vault_->GetUserId();
  if (!UserHandler::UserIdExists(user_id)) {
    util::PrintErrorMessage("Invalid user ID. Cannot add entry.\n\n");
    return;
  }
  EntryHandler::AddEntry(new_entry, user_id);

  util::PrintSuccessMessage("Entry added successfully!\n\n");
}