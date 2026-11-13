#pragma once

#include <iostream>
#include <string>
#include <cstdint>

struct ProcessInfo
{
    std::uint32_t pid;
    std::uint32_t parentPid;
    std::wstring exeName;
    std::wstring imagePath;

    // Declared as a friend (non-member) so the stream is the left operand:
    // `std::wcout << process`. As a member it would have to be `process << stream`.
    friend std::wostream& operator<<(std::wostream& os, const ProcessInfo& pi) {
        os << pi.pid << L' ' 
            << pi.parentPid << L' ' 
            << pi.exeName << L' '
            << pi.imagePath << L'\n';
        return os;
    }
};

