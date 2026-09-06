#include "include/delete_entry_command.h"

#include "util/print.h"

static constexpr auto kCommandName{"delete"};
static constexpr auto kCommandDescription{"Delete an existing entry"};
static constexpr auto kCommandHeader{"Delete Entry"};

namespace {

void PrintResult(const bool& result) {
  if (result) {
    util::PrintSuccessMessage("Deleted entry successfully!");
  } else {
    util::PrintWarningMessage("An error occured during deleting entry!");
  }
  std::cout << "\n\n";
}

}  // namespace

DeleteEntryCommand::DeleteEntryCommand(Vault::Ptr vault)
    : Command(kCommandName, kCommandDescription), vault_(vault) {}

void DeleteEntryCommand::Execute() {
  util::PrintCommandHeader(kCommandHeader);

  try {
    auto input_id = ReadInputLine("Select Id: ");
    auto selected_id = std::stoi(input_id);
    auto result = vault_->DeleteEntryById(selected_id);
    PrintResult(result);

  } catch (const std::invalid_argument&) {
    util::PrintErrorMessage(
        "Invalid input. Please enter a valid command index.\n");
  } catch (const std::out_of_range&) {
    util::PrintErrorMessage(
        "Input out of range. Please enter a valid command index.\n");
  }
}

void DeleteEntryCommand::DeleteEntryById() {}