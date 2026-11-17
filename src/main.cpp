#include "agent/ProcessEnumerator.h"
#include "agent/KnownFolders.h"
#include "agent/SuspiciousLocationRule.h"

#include <iostream>

int main(void)
{
    std::wstring downloads = GetDownloadsDirectory();
    std::wstring temp = GetTempDirectory();

    std::wcout << downloads << L'\n' << temp << L"\n\n";

    SuspiciousLocationRule rule({ downloads, temp });

    std::vector<ProcessInfo> processes = EnumerateProcesses();

    for(const auto& process : processes) {
        std::optional<Alert> alert = rule.Evaluate(process);

        if (alert.has_value()) {
            std::wcout << alert->ruleName << L' '
                << alert->process.pid << L' '
                << alert->process.exeName << L' '
                << alert->details << L'\n';
        }
    }                  

    return 0;
}
