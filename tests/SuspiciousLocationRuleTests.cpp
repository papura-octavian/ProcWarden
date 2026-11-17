#include <gtest/gtest.h>

#include "agent/SuspiciousLocationRule.h"

TEST(SuspiciousLocationRule, AlertsForProcessInWatchedDirectory)
{
    SuspiciousLocationRule rule({ L"C:\\Test\\Downloads", L"C:\\Test\\Temp" });

    ProcessInfo process{ 1234, 4, L"evil.exe", L"C:\\Test\\Downloads\\evil.exe" };

    std::optional<Alert> result = rule.Evaluate(process);

    EXPECT_TRUE(result.has_value());
}

TEST(SuspiciousLocationRule, AlertsForProcessInSecondWatchedDirectory)
{
    SuspiciousLocationRule rule({ L"C:\\Test\\Downloads", L"C:\\Test\\Temp" });

    ProcessInfo process{ 1234, 4, L"evil.exe", L"C:\\Test\\Temp\\evil.exe" };

    std::optional<Alert> result = rule.Evaluate(process);

    EXPECT_TRUE(result.has_value());
}