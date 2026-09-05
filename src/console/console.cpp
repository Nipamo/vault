#include "console.h"

#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>

#include "entry.h"
#include "util/print.h"
#include "vault.h"

constexpr auto kCommandPrefix{"vault"};

Console::Console(Vault::Ptr vault) : vault_(vault) {
  // The order of command creation matters, as it determines the order in which
  // commands are displayed in the menu and which index they are assigned.
  CreateAddEntryCommand();
  CreateListEntriesCommand();
  CreateMenuCommand();
  CreateExitCommand();
}

void Console::Run() {
  while (true) {
    if (vault_->IsLocked()) {
      AskForPasswordAndOpenVault();
      PrintMenu();
    }

    std::string input_command = ReadInputLine("Select a command: ");

    try {
      int input_index = std::stoi(input_command);
      auto command_iterator = command_map_.find(input_index);
      if (command_iterator != command_map_.end()) {
        command_iterator->second.action_();
      } else {
        util::PrintErrorMessage("Invalid command index. Please try again.\n");
      }
    } catch (const std::invalid_argument&) {
      util::PrintErrorMessage(
          "Invalid input. Please enter a valid command index.\n");
    } catch (const std::out_of_range&) {
      util::PrintErrorMessage(
          "Input out of range. Please enter a valid command index.\n");
    }
  }
}

void Console::CreateAddEntryCommand() {
  Command add_entry_command;
  add_entry_command.name_ = "add";
  add_entry_command.description_ = "Add a new entry";
  add_entry_command.action_ = [this]() { this->AddEntryCommand(); };
  command_map_[++command_index_] = add_entry_command;
}

void Console::CreateListEntriesCommand() {
  Command list_entries_command;
  list_entries_command.name_ = "list";
  list_entries_command.description_ = "List all entries";
  list_entries_command.action_ = [this]() { this->ListEntriesCommand(); };
  command_map_[++command_index_] = list_entries_command;
}

void Console::CreateMenuCommand() {
  Command menu_command;
  menu_command.name_ = "menu";
  menu_command.description_ = "Show the command menu";
  menu_command.action_ = [this]() { this->PrintMenu(); };
  command_map_[++command_index_] = menu_command;
}

void Console::CreateExitCommand() {
  Command exit_command;
  exit_command.name_ = "exit";
  exit_command.description_ = "Exit the application";
  exit_command.action_ = []() { std::exit(0); };
  command_map_[++command_index_] = exit_command;
}

void Console::AskForPasswordAndOpenVault() {
  if (vault_->IsLocked()) {
    util::PrintInfoMessage("Vault is locked.\n\nMaster password: ");

    do {
      std::string input_password;
      std::getline(std::cin, input_password);
      if (input_password == vault_->GetMasterPassword()) {
        vault_->Unlock();
        util::PrintSuccessMessage("Vault unlocked!\n\n");
      } else {
        util::PrintErrorMessage("Wrong password! Try again:");
      }
    } while (vault_->IsLocked());
  }
}

void Console::PrintMenu() {
  util::PrintCommandHeader("Command Menu");
  for (const auto& command : command_map_) {
    std::cout << command.first << " - " << command.second.description_ << "\n";
  }

  std::cout << "\n";
}

void Console::AddEntryCommand() {
  util::PrintCommandHeader("Add Entry");

  std::string service = ReadInputLine("Service: ");
  std::string username = ReadInputLine("Username: ");
  std::string password = ReadInputLine("Password: ");
  std::string notes = ReadInputLine("Notes: ");

  Entry new_entry = {.service = service,
                     .username = username,
                     .password = password,
                     .notes = notes};
  vault_->AddEntry(new_entry);

  util::PrintSuccessMessage("Entry added successfully!\n\n");
}

void Console::ListEntriesCommand() {
  const auto& entries = vault_->GetEntries();

  if (entries.empty()) {
    util::PrintInfoMessage("No entries found.\n\n");
    return;
  }

  util::PrintCommandHeader("List Entries");

  std::cout << std::left << std::setw(6) << "ID" << std::setw(24) << "Service"
            << std::setw(28) << "Username" << std::setw(16) << "Password"
            << std::setw(34) << "Notes"
            << "\n";

  std::cout << std::string(108, '-') << "\n";

  for (const auto& entry : entries) {
    std::string notes = entry.notes;
    std::string password_masked = std::string(entry.password.length(), '*');

    constexpr std::size_t max_note_length = 31;

    if (notes.length() > max_note_length) {
      notes = notes.substr(0, max_note_length) + "...";
    }

    std::cout << std::left << std::setw(6) << entry.id << std::setw(24)
              << entry.service << std::setw(28) << entry.username
              << std::setw(16) << password_masked << std::setw(34) << notes
              << "\n";
  }
  std::cout << "\n";

  std::string entry_label = entries.size() == 1 ? "entry" : "entries";
  std::ostringstream message_stream;
  message_stream << entries.size() << " " << entry_label << ".\n\n";
  util::PrintInfoMessage(message_stream.str());
}

auto Console::ReadInputLine(const std::string& prompt) -> std::string& {
  std::cout << prompt;
  static std::string input_line;
  std::getline(std::cin, input_line);
  return input_line;
}