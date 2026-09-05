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
  std::string notes = Command::ReadInputLine("Notes: ");

  Entry new_entry = {.service = service,
                     .username = username,
                     .password = password,
                     .notes = notes};

  return new_entry;
}

}  // namespace

AddEntryCommand::AddEntryCommand(Vault::Ptr vault)
    : Command(kCommandName, kCommandDescription, {}), vault_(vault) {}

void AddEntryCommand::Execute() {
  util::PrintCommandHeader(kCommandHeader);

  Entry new_entry;
  new_entry = CreateEntryFromInput();
  vault_->AddEntry(new_entry);

  util::PrintSuccessMessage("\nEntry added successfully!\n\n");
}