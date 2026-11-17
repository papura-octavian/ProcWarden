#pragma once

#include "agent/Alert.h"
#include <optional>

class IDetectionRule {
public:
    virtual ~IDetectionRule() = default;
    virtual std::optional<Alert> Evaluate(const ProcessInfo& process) const = 0;
};