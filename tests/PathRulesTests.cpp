#include <gtest/gtest.h>

#include "agent/PathRules.h"

TEST(IsUnderDirectory, FileDirectlyInDirectory) {
    EXPECT_TRUE(IsUnderDirectory(
        L"C:\\Users\\test\\Downloads\\a.exe",
        L"C:\\Users\\test\\Downloads"
    ));
}

TEST(IsUnderDirectory, FileInSubdirectory) {
    EXPECT_TRUE(IsUnderDirectory(
        L"C:\\Users\\test\\Downloads\\subdir\\a.exe",
        L"C:\\Users\\test\\Downloads"
    ));
}