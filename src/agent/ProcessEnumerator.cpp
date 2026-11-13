#include "ProcessEnumerator.h"
#include "common/UniqueHandle.h"

#include <windows.h>
#include <tlhelp32.h>   

namespace {
    std::wstring QueryImagePath(DWORD pid) {
        UniqueHandle process(OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid));
        if(!process.IsValid()) {
            return {};
        }

        std::wstring path(32768, L'\0');
        DWORD size = static_cast<DWORD> (path.size());

        if (!QueryFullProcessImageNameW(process.Get(), 0, path.data(), &size))
        {
            return {};
        }

        path.resize(size);
        return path;
    }
}

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
            entry.szExeFile,
            QueryImagePath(entry.th32ProcessID)
       }); 
    } while (Process32NextW(snapshot.Get(), &entry));

    return processes;
}