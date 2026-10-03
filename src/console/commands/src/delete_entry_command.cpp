#include "include/delete_entry_command.h"

#include <entry_handler.h>

#include "util/print.h"

static constexpr auto kCommandName{"delete"};
static constexpr auto kCommandDescription{"Delete an existing entry"};
static constexpr auto kCommandHeader{"Delete Entry"};

DeleteEntryCommand::DeleteEntryCommand(Vault::Ptr vault)
    : Command(kCommandName, kCommandDescription), vault_(vault) {}

void DeleteEntryCommand::Execute() {
  util::PrintCommandHeader(kCommandHeader);

  try {
    auto input_id = ReadInputLine("Select Id: ");
    auto selected_id = std::stoi(input_id);
    if (EntryHandler::GetEntryById(selected_id)->user_id !=
        Vault::GetUserId()) {
      util::PrintErrorMessage(
          "You do not have permission to delete this entry.\n");
      return;
    }
    EntryHandler::DeleteEntry(selected_id);
    util::PrintSuccessMessage("Deleted entry successfully!\n\n");

  } catch (const std::invalid_argument&) {
    util::PrintErrorMessage(
        "Invalid input. Please enter a valid command index.\n");
  } catch (const std::out_of_range&) {
    util::PrintErrorMessage(
        "Input out of range. Please enter a valid command index.\n");
  }
}

void DeleteEntryCommand::DeleteEntryById() {}