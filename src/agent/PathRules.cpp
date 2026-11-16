#include "agent/PathRules.h"

bool IsUnderDirectory(std::wstring_view path, std::wstring_view directory) {
    while(true) {
        if(path[path.size() - 1] == L'\\') {
            path.remove_suffix(1);
            break;
        }

        path.remove_suffix(1);
    }

    return path == directory;
}