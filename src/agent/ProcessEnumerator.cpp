#include "ProcessEnumerator.h"

std::vector<ProcessInfo> EnumerateProcesses(void) {
    std::vector<ProcessInfo> vec;

    vec.push_back(ProcessInfo(4, 0, L"System"));
    vec.push_back(ProcessInfo(1234, 4, L"Notepad.exe"));

    return vec;
}