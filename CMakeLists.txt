cmake_minimum_required(VERSION 3.25)

project(ProcWarden
    VERSION 0.1.0
    DESCRIPTION "User-mode security monitoring agent for Windows (EDR-lite)"
    LANGUAGES CXX
)

# Standard C++20, fara extensii specifice compilatorului
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Genereaza compile_commands.json (util pentru IntelliSense / clang-tidy mai tarziu)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT MSVC)
    message(FATAL_ERROR "Proiectul asta e gandit pentru MSVC pe Windows.")
endif()

add_executable(procwarden
    src/main.cpp
)

target_compile_options(procwarden PRIVATE
    /W4           # avertismente stricte
    /permissive-  # conformitate stricta cu standardul
    /utf-8        # surse si executie in UTF-8
    /sdl          # verificari suplimentare de securitate (SDL)
    /Zc:__cplusplus
)

target_compile_definitions(procwarden PRIVATE
    UNICODE _UNICODE      # API-urile Win32 in varianta W (wide char)
    WIN32_LEAN_AND_MEAN   # windows.h mai mic
    NOMINMAX              # fara macro-urile min/max care strica std::min/std::max
    _WIN32_WINNT=0x0A00   # tinta: Windows 10+
)
