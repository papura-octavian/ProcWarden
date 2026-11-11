#include "agent/ProcessEnumerator.h"

int main(void)
{
    std::vector<ProcessInfo> processes = EnumerateProcesses();

    for(const auto& process : processes) {
        std::wcout << process;
    }

    return 0;
}
