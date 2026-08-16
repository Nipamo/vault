#include "console.h"
#include "entry.h"
#include "vault.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace src::console {

constexpr auto kCommandPrefix = "vault";
constexpr auto kAddEntryCommand = "add";
constexpr auto kGetEntriesCommand = "get";

Console::Console(Vault::Ptr vault) : vault_ptr_(vault) { Run(); }

void Console::Run() {
  while (true) {
    std::string command;
    std::getline(std::cin, command);

    if (command == "") {
      continue;
    }

    std::istringstream iss(command);
    std::vector<std::string> arguments;
    std::string argument;

    while (iss >> argument) {
      arguments.push_back(argument);
    }

    std::string entered_prefix = arguments[0];

    if (entered_prefix == kCommandPrefix) {
      if (vault_ptr_ == nullptr) {
        vault_ptr_ = std::make_shared<Vault>();
      }

      if (arguments.size() > 1) {
        std::string argument_1 = arguments[1];

        if (argument_1 == kAddEntryCommand) {
          vault::Entry new_entry;
          new_entry.name = ReadInputWithMessage("Name: ");
          new_entry.user_name = ReadInputWithMessage("Username: ");
          new_entry.password = ReadInputWithMessage("Password: ");
          new_entry.notes = ReadInputWithMessage("Notes: ");

          vault_ptr_->AddEntry(new_entry);

          PrintMessage("Successfully added Entry!");
        } else if (argument_1 == kGetEntriesCommand) {
          for (const auto& entry : vault_ptr_->GetEntries()) {
            std::cout << entry;
          }
        }
      }
    }
  }
}

void Console::PrintMessage(const std::string& message) {
  std::cout << "> " << message << "\n";
}

auto Console::ReadInputWithMessage(const std::string& message) -> std::string {
  std::cout << message;
  std::string input;
  std::cin >> input;
  return input;
}

} // namespace src::console