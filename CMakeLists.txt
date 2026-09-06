cmake_minimum_required(VERSION 3.20)

project(vault
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(vault
    src/main.cpp
    src/vault.cpp
    src/vault.h
    src/console/console.cpp
    src/console/commands/command.cpp
    src/console/commands/src/add_entry_command.cpp
    src/console/commands/src/list_entries_command.cpp
    src/console/commands/src/edit_entry_command.cpp
    src/console/commands/src/delete_entry_command.cpp
    src/entry.h
    src/util/print.h
)

target_include_directories(vault PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/console
    ${CMAKE_CURRENT_SOURCE_DIR}/src/console/commands
    ${CMAKE_CURRENT_SOURCE_DIR}/src/console/commands/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/console/commands/src
)