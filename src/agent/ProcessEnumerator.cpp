#include "ProcessEnumerator.h"
#include "common/UniqueHandle.h"

#include <windows.h>
#include <tlhelp32.h>   

std::vector<ProcessInfo> EnumerateProcesses(void) {
    std::vector<ProcessInfo> processes;

    UniqueHandle snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
    if(!snapshot.IsValid()) {
        return processes;
    }

    PROCESSENTRY32W entry {};
    entry.dwSize = sizeof(entry);

    if(!Process32FirstW(snapshot.Get(), &entry)) {
        return processes;
    }

    do {
       processes.push_back({
            entry.th32ProcessID,
            entry.th32ParentProcessID,
            entry.szExeFile
       }); 
    } while (Process32NextW(snapshot.Get(), &entry));

    return processes;
}