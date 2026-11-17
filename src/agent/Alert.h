#pragma once

#include <string>
#include "agent/ProcessInfo.h"

struct Alert {
    std::wstring ruleName;
    ProcessInfo process;
    std::wstring details;
};