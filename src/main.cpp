#include "agent/ProcessEnumerator.h"
#include "common/UniqueHandle.h"

constexpr wchar_t kNewline = L'\n';

int main(void)
{
    std::vector<ProcessInfo> processes = EnumerateProcesses();

    for(const auto& process : processes) {
        std::wcout << process;
    }

    return 0;
}
