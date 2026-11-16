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

TEST(IsUnderDirectory, PathIsShortherThanDirectory) {
    EXPECT_FALSE(IsUnderDirectory(
        L"C:\\Users",
        L"C:\\Users\\test\\Downloads"
    ));
}

TEST(IsUnderDirectory, SiblingDirectoryWithSamePrefix) {
    EXPECT_FALSE(IsUnderDirectory(
        L"C:\\Users\\test\\DownloadsOld\\a.exe",
        L"C:\\Users\\test\\Downloads"
    ));
}