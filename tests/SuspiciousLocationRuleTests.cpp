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

TEST(SuspiciousLocationRule, NoAlertForProcessOutsideWatchedDirectories)
{
    SuspiciousLocationRule rule({ L"C:\\Test\\Downloads", L"C:\\Test\\Temp" });

    ProcessInfo process{ 1234, 4, L"svchost.exe", L"C:\\Windows\\System32\\svchost.exe" };

    std::optional<Alert> result = rule.Evaluate(process);

    EXPECT_FALSE(result.has_value());
}

TEST(SuspiciousLocationRule, NoAlertWhenImagePathIsUnknown)
{
    SuspiciousLocationRule rule({ L"C:\\Test\\Downloads", L"C:\\Test\\Temp" });

    ProcessInfo process{ 1234, 4, L"lsass.exe", L"" };

    std::optional<Alert> result = rule.Evaluate(process);

    EXPECT_FALSE(result.has_value());
}

TEST(SuspiciousLocationRule, NoAlertWhenNoDirectoriesConfigured)
{
    SuspiciousLocationRule rule({});

    ProcessInfo process{ 1234, 4, L"evil.exe", L"C:\\Test\\Temp\\evil.exe" };

    std::optional<Alert> result = rule.Evaluate(process);

    EXPECT_FALSE(result.has_value());
}

TEST(SuspiciousLocationRule, AlertContainsRuleNameAndProcess)
{
    SuspiciousLocationRule rule({ L"C:\\Test\\Downloads", L"C:\\Test\\Temp" });

    ProcessInfo process{ 1234, 4, L"evil.exe", L"C:\\Test\\Downloads\\evil.exe" };

    std::optional<Alert> result = rule.Evaluate(process);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->ruleName, L"SuspiciousLocation");
    EXPECT_EQ(result->process.pid, 1234);
    EXPECT_FALSE(result->details.empty());
}