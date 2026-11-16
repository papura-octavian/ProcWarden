#include "agent/PathRules.h"

bool IsUnderDirectory(std::wstring_view path, std::wstring_view directory) {
    for(int it = 0; it < directory.size(); it++) {
        if(directory[it] != path[it]) {
            return false;
        }
    }

    return true;
}