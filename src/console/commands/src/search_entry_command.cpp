#include "include/search_entry_command.h"

#include <entry_handler.h>

#include <cctype>
#include <stdexcept>

#include "util/print.h"

static constexpr auto kCommandName{"search"};
static constexpr auto kCommandDescription{"Search entry by service or ID"};
static constexpr auto kCommandHeader{"Search Entry"};

namespace {

auto IsNumber(const std::string& string) {
  for (char c : string) {
    if (!std::isdigit(c)) {
      return false;
    }
  }
  return true;
}

}  // namespace

SearchEntryCommand::SearchEntryCommand(Vault::Ptr vault)
    : Command(kCommandName, kCommandDescription), vault_(vault) {}

void SearchEntryCommand::Execute() {
  util::PrintCommandHeader(kCommandHeader);

  try {
    auto input = ReadInputLine("Select ID or Service: ");

    std::cout << "\n";

    if (IsNumber(input)) {
      auto selected_id = std::stoi(input);
      std::cout << *EntryHandler::GetEntryById(selected_id) << "\n";
    } else {
      auto found_entry = false;
      for (const auto& entry : EntryHandler::GetEntries()) {
        if (found_entry) {
          std::cout << "--------------\n";
        }

        if (entry->service == input) {
          std::cout << *entry << "\n";
          found_entry = true;
        }
      }

      if (!found_entry) {
        util::PrintInfoMessage("No entry with service: " + input + " found!\n");
      }
    }

    std::cout << "\n";
  } catch (const std::out_of_range& e) {
    util::PrintErrorMessage("Invalid ID selected!\n\n");
  } catch (...) {
    util::PrintErrorMessage("Something went wrong!\n\n");
  }
}