#include "console.h"

#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>

#include "entry.h"
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
        std::cout << "Invalid command index. Please try again.\n";
      }
    } catch (const std::invalid_argument&) {
      std::cout << "Invalid input. Please enter a valid command index.\n";
    } catch (const std::out_of_range&) {
      std::cout << "Input out of range. Please enter a valid command index.\n";
    }
  }
}

void Console::PrintMenu() {
  std::cout << "Available commands:\n";
  for (const auto& command : command_map_) {
    std::cout << command.first << " - " << command.second.description_ << "\n";
  }

  std::cout << "\n";
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
    std::cout << "Vault is locked.\n\n"
              << "Master password: ";
    do {
      std::string input_password;
      std::getline(std::cin, input_password);
      if (input_password == vault_->GetMasterPassword()) {
        vault_->Unlock();
        std::cout << "Vault unlocked!\n\n";
      } else {
        std::cout << "Wrong password! Try again: ";
      }
    } while (vault_->IsLocked());
  }
}

void Console::AddEntryCommand() {
  std::cout << "--- Add Entry ---\n\n";

  std::string service = ReadInputLine("Service: ");
  std::string username = ReadInputLine("Username: ");
  std::string password = ReadInputLine("Password: ");
  std::string notes = ReadInputLine("Notes: ");

  Entry new_entry = {.service = service,
                     .username = username,
                     .password = password,
                     .notes = notes};
  vault_->AddEntry(new_entry);

  std::cout << "Entry added successfully!\n\n";
}

void Console::ListEntriesCommand() {
  const auto& entries = vault_->GetEntries();

  std::cout << "\n--- Vault Entries ---\n\n";

  std::cout << std::left << std::setw(6) << "ID" << std::setw(24) << "Service"
            << std::setw(28) << "Username" << std::setw(16) << "Password"
            << std::setw(34) << "Notes"
            << "\n";

  std::cout << std::string(108, '-') << "\n";

  for (const auto& entry : entries) {
    std::string notes = entry.notes;

    constexpr std::size_t max_note_length = 31;

    if (notes.length() > max_note_length) {
      notes = notes.substr(0, max_note_length) + "...";
    }

    std::cout << std::left << std::setw(6) << entry.id << std::setw(24)
              << entry.service << std::setw(28) << entry.username
              << std::setw(16) << "*****" << std::setw(34) << notes << "\n";
  }

  std::cout << "\n" << entries.size() << " entry(ies).\n\n";
}

auto Console::ReadInputLine(const std::string& prompt) -> std::string& {
  std::cout << prompt;
  static std::string input_line;
  std::getline(std::cin, input_line);
  return input_line;
}