#include "agent/PathRules.h"
#include <string>
#include <algorithm>

bool IsUnderDirectory(std::wstring_view path, std::wstring_view directory) {
    if(path.size() <= directory.size() ||
        path.empty() || 
        directory.empty()) return false;

    auto CheckWord = [](std::size_t& index, std::wstring_view str) {
        std::wstring result = L"";
        while (index < str.size()) {
            if (str[index] == L'\\') {
                index++;
                std::transform(begin(result), end(result), begin(result), ::towlower);
                return result;
            }
            
            result += str[index++];
        }

        std::transform(begin(result), end(result), begin(result), ::towlower);
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

    // special case Path is bigger than Directory
    // but it's just one `\` and not a file 
    second = CheckWord(itPath, path);
    if (second.empty()) {
        return false;
    }

    return true;
}