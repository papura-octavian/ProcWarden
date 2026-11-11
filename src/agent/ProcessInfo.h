#pragma once

#include <iostream>
#include <string>

struct ProcessInfo
{
    int pid;
    int parentPid;
    std::wstring exeName;

    friend std::wostream& operator<<(std::wostream& os, const ProcessInfo& pi) {
        os << pi.pid << L" " << pi.parentPid << L" " << pi.exeName << std::endl;
        return os;
    }
};

