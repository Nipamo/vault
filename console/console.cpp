#include "console.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "entry.h"
#include "vault.h"

constexpr auto kCommandPrefix{"vault"};

Console::Console(Vault::Ptr vault) : vault_(vault) {}

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

void Console::Run() {
  while (true) {
    AskForPasswordAndOpenVault();

    std::string input_command;
    getline(std::cin, input_command);

    if (input_command == "add") {
      AddEntryCommand();
    } else if (input_command == "list") {
      ListEntriesCommand();
    }
  }
}
