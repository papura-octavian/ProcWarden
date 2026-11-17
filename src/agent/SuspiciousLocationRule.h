#pragma once

#include "agent/IDetectionRule.h"
#include "agent/PathRules.h"
#include <vector>
#include <utility>

class SuspiciousLocationRule : public IDetectionRule{
private:
    std::vector<std::wstring> _directories;
public:
    explicit SuspiciousLocationRule(std::vector<std::wstring> directories) 
        : _directories(std::move(directories))
    { 
    }

    std::optional<Alert> Evaluate(const ProcessInfo& process) const override {
        if(_directories.empty()) {
            return std::nullopt;
        }

        for (const auto& dir : _directories) {
            if (IsUnderDirectory(process.imagePath, dir)) {
                return Alert {
                    L"SuspiciousLocation",
                    process,
                    L"Executable runs from watched directory " + dir
                };
            }
        }

        return std::nullopt;
    }
};