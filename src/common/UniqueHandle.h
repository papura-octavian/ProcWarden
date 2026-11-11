#pragma once

#include <windows.h>
#include <utility>

class UniqueHandle
{
private:
    HANDLE m_handle = nullptr;
public:
    UniqueHandle() = default;

    explicit UniqueHandle(HANDLE handle) : m_handle(handle) {}

    ~UniqueHandle() { Reset(); }

    // Problem : Objects with the same Handler would both call CloseHandle
    // and the second one could get over other resources
    // FIX : Any coppy would result in a compile error
    UniqueHandle(const UniqueHandle&) = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    UniqueHandle(UniqueHandle&& other) noexcept 
        : m_handle(std::exchange(other.m_handle, nullptr)) 
    {

    }

    UniqueHandle& operator=(UniqueHandle&& other) noexcept {
        if(this != &other) {
            Reset(std::exchange(other.m_handle, nullptr));
        }
        return *this;
    }

    void Reset(HANDLE handle = nullptr) noexcept {
        if(IsValid()){
            CloseHandle(m_handle);
        }
        m_handle = handle;
    }

    bool IsValid() const {
        return m_handle != nullptr && m_handle != INVALID_HANDLE_VALUE;
    }

    HANDLE Get() const {
        return m_handle;
    }
};
