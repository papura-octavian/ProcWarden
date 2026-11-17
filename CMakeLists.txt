cmake_minimum_required(VERSION 3.25)

project(ProcWarden
    VERSION 0.1.0
    DESCRIPTION "User-mode security monitoring agent for Windows (EDR-lite)"
    LANGUAGES CXX
)

# C++20, no compiler-specific extensions
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json (IntelliSense, clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT MSVC)
    message(FATAL_ERROR "This project targets MSVC on Windows.")
endif()

# ===== Core library: all logic, no main() =====
add_library(procwarden_core STATIC
    src/agent/ProcessEnumerator.cpp
    src/agent/PathRules.cpp
    src/agent/KnownFolders.cpp
)

target_include_directories(procwarden_core PUBLIC src)

target_compile_options(procwarden_core PUBLIC
    /W4           # strict warnings
    /permissive-  # strict standard conformance
    /utf-8        # UTF-8 source and execution charset
    /sdl          # additional security checks (SDL)
    /Zc:__cplusplus
)

target_compile_definitions(procwarden_core PUBLIC
    UNICODE _UNICODE      # wide-char (W) Win32 APIs
    WIN32_LEAN_AND_MEAN   # smaller windows.h
    NOMINMAX              # no min/max macros
    _WIN32_WINNT=0x0A00   # target Windows 10+
)

# ===== Agent executable =====
add_executable(procwarden
    src/main.cpp
)

target_link_libraries(procwarden PRIVATE procwarden_core)

# ===== Unit tests =====
enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(procwarden_tests
    tests/SanityTests.cpp
    tests/PathRulesTests.cpp
    tests/SuspiciousLocationRuleTests.cpp
)

target_link_libraries(procwarden_tests PRIVATE
    procwarden_core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(procwarden_tests)