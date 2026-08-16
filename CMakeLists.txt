cmake_minimum_required(VERSION 3.20)

project(vault
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src src/vault src/console)

add_executable(vault
    src/main.cpp
    src/vault/vault.cpp
    src/vault/vault.h
    src/vault/entry.h
    src/console/console.cpp
    src/console/console.h
)