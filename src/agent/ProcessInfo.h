#pragma once

#include <iostream>
#include <string>

struct ProcessInfo
{
    int pid;
    int parentPid;
    std::wstring exeName;

    // Declared as a friend (non-member) so the stream is the left operand:
    // `std::wcout << process`. As a member it would have to be `process << stream`.
    friend std::wostream& operator<<(std::wostream& os, const ProcessInfo& pi) {
        os << pi.pid << L" " << pi.parentPid << L" " << pi.exeName << std::endl;
        return os;
    }
};

