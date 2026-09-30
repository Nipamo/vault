#include "console.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>

#include "command.h"
#include "commands/include/add_entry_command.h"
#include "commands/include/delete_entry_command.h"
#include "commands/include/edit_entry_command.h"
#include "commands/include/list_entries_command.h"
#include "commands/include/search_entry_command.h"
#include "util/print.h"
#include "vault.h"

Console::Console(Vault::Ptr vault) : vault_(vault) { InitCommands(); }

void Console::InitCommands() {
  int command_index{0};

  AddEntryCommand::Ptr add_entry_command =
      std::make_shared<AddEntryCommand>(vault_);
  EditEntryCommand::Ptr edit_entry_command =
      std::make_shared<EditEntryCommand>(vault_);
  ListEntriesCommand::Ptr list_entries_command =
      std::make_shared<ListEntriesCommand>(vault_);
  DeleteEntryCommand::Ptr delete_entry_command =
      std::make_shared<DeleteEntryCommand>(vault_);
  SearchEntryCommand::Ptr search_entry_command =
      std::make_shared<SearchEntryCommand>(vault_);
  Command::Ptr menu_command = std::make_shared<Command>(
      "menu", "Show the command menu", [this]() { this->PrintMenu(); });
  Command::Ptr exit_command = std::make_shared<Command>(
      "exit", "Exit the application", []() { std::exit(0); });

  command_map_[++command_index] = add_entry_command;
  command_map_[++command_index] = edit_entry_command;
  command_map_[++command_index] = list_entries_command;
  command_map_[++command_index] = search_entry_command;
  command_map_[++command_index] = delete_entry_command;
  command_map_[++command_index] = menu_command;
  command_map_[++command_index] = exit_command;
}

void Console::Run() {
  while (true) {
    // Only print the menu right after accessing the vault. Not after each input
    while (vault_->IsLocked()) {
      if (UnlockVault()) {
        vault_->Unlock();
        PrintMenu();
      }
    }

    std::string input_command = Command::ReadInputLine("Select a command: ");

    try {
      int input_index = std::stoi(input_command);
      TryExecuteCommand(input_index);
    } catch (const std::invalid_argument&) {
      util::PrintErrorMessage(
          "Invalid input. Please enter a valid command index.\n");
    } catch (const std::out_of_range&) {
      util::PrintErrorMessage(
          "Input out of range. Please enter a valid command index.\n");
    }
  }
}

auto Console::UnlockVault() -> bool {
  util::PrintInfoMessage("Vault is locked.\n\n");

  std::cout << "Username: ";
  std::string username_input;
  std::getline(std::cin, username_input);

  if (user_handler_.UsernameExists(username_input)) {
    std::cout << "Password: ";
    std::string password_input;
    std::getline(std::cin, password_input);
    if (user_handler_.ValidatePassword(username_input, password_input)) {
      util::PrintSuccessMessage("Unlocked vault!\n");
      return true;
    }

    util::PrintErrorMessage("Wrong password!\n");
    return false;
  }

  std::cout << "Create new account? (y/N): ";
  std::string input;
  std::getline(std::cin, input);

  if (input == "y") {
    return CreateNewAccount();
  }

  return false;
}

auto Console::CreateNewAccount() -> bool {
  std::cout << "Username: ";
  std::string username;
  std::getline(std::cin, username);

  std::cout << "Password: ";
  std::string password;
  std::getline(std::cin, password);

  user_handler_.CreateNewAccount(username, password);

  return true;
}

void Console::PrintMenu() {
  util::PrintCommandHeader("Command Menu");
  for (const auto& command : command_map_) {
    int command_index = command.first;
    std::string command_description = command.second->description();
    std::cout << command_index << " - " << command_description << "\n";
  }

  std::cout << "\n";
}

void Console::TryExecuteCommand(const int& command_index) {
  auto command_iterator = command_map_.find(command_index);
  if (command_iterator != command_map_.end()) {
    command_iterator->second->Execute();
  } else {
    util::PrintErrorMessage("Invalid command index. Please try again.\n");
  }
}

auto Console::ValidatePassword(const std::string& password) -> bool {
  if (password == vault_->GetMasterPassword()) {
    util::PrintSuccessMessage("Vault unlocked!\n\n");
    return true;
  } else {
    util::PrintErrorMessage("Wrong password! Try again: ");
    return false;
  }
}
