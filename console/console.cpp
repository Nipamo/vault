#include "console.h"
#include "entry.h"
#include "vault.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>

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

  Entry new_entry = {
      .service = service, .username = username, .password = password};
  vault_->AddEntry(new_entry);

  std::cout << "Entry added successfully!\n\n";
}

void Console::ListEntriesCommand() {
  const auto& entries = vault_->GetEntries();

  std::cout << "\n--- Vault Entries ---\n\n";

  std::cout << std::left << std::setw(6) << "ID" << std::setw(24) << "Service"
            << std::setw(28) << "Username"
            << "Password\n";

  std::cout << std::string(80, '-') << "\n";

  for (const auto& entry : entries) {
    std::cout << std::left << std::setw(6) << entry.id << std::setw(24)
              << entry.service << std::setw(28) << entry.username
              << entry.password << "\n";
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
