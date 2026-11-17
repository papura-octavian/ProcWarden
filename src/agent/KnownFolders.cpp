#include "agent/KnownFolders.h"
#include <windows.h>
#include <shlobj.h> 
#include <memory>

std::wstring GetDownloadsDirectory(void) {
    PWSTR rawPath = nullptr;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Downloads, 0, nullptr, &rawPath);

    // SHGetKnownFolderPath allocates the string; it must be freed with
    // CoTaskMemFree even when the call fails.
    std::unique_ptr<wchar_t, decltype(&CoTaskMemFree)> path(rawPath, &CoTaskMemFree);

    if (SUCCEEDED(hr)) {
        return std::wstring(path.get());
    }

    return {};
}

std::wstring GetTempDirectory(void) {
    wchar_t buffer[MAX_PATH + 1];
    DWORD length = GetTempPathW(MAX_PATH + 1, buffer);

    if (length == 0 || length >= MAX_PATH + 1) {
        return {};
    }

    return std::wstring(buffer, length);
}