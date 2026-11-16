#include "agent/PathRules.h"
#include <string>

bool IsUnderDirectory(std::wstring_view path, std::wstring_view directory) {
    if(path.size() < directory.size()) return false;

    auto CheckWord = [](std::size_t& index, std::wstring_view str) {
        std::wstring result = L"";
        while (index < str.size()) {
            if (str[index] == L'\\') {
                index++;
                return result;
            }
            
            result += str[index++];
        }

        return result;
    };

    std::wstring first = L"", second = L"";
    std::size_t itPath = 0, itDir = 0;
    while(itDir < directory.size()) {
        first = CheckWord(itDir, directory);
        second = CheckWord(itPath, path);
        if (first != second) {
            return false;
        }
    }

    return true;
}