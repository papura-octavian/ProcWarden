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
        return std::nullopt;
    }
};