#pragma once

#include <windows.h>

class UniqueHandle
{
private:
    HANDLE m_handle = nullptr;
public:
    UniqueHandle() = default;

    explicit UniqueHandle(HANDLE handle) : m_handle(handle) {}

    ~UniqueHandle() {
        if(IsValid()) {
            CloseHandle(m_handle);
        }
    }

    // Problem : Objects with the same Handler would both call CloseHandle
    // and the second one could get over other resources
    // FIX : Any coppy would result in a compile error
    UniqueHandle(const UniqueHandle&) = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    bool IsValid() const {
        return m_handle != nullptr && m_handle != INVALID_HANDLE_VALUE;
    }

    HANDLE Get() const {
        return m_handle;
    }
};
