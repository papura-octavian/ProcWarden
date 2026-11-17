#pragma once

#include <windows.h>
#include <utility>

class UniqueHandle
{
private:
    HANDLE _handle = nullptr;
public:
    UniqueHandle() = default;

    explicit UniqueHandle(HANDLE handle) : _handle(handle) {}

    ~UniqueHandle() { Reset(); }

    // Problem : Objects with the same Handler would both call CloseHandle
    // and the second one could get over other resources
    // FIX : Any coppy would result in a compile error
    UniqueHandle(const UniqueHandle&) = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    UniqueHandle(UniqueHandle&& other) noexcept 
        : _handle(std::exchange(other._handle, nullptr)) 
    {

    }

    UniqueHandle& operator=(UniqueHandle&& other) noexcept {
        if(this != &other) {
            Reset(std::exchange(other._handle, nullptr));
        }
        return *this;
    }

    void Reset(HANDLE handle = nullptr) noexcept {
        if(IsValid()){
            CloseHandle(_handle);
        }
        _handle = handle;
    }

    bool IsValid() const {
        return _handle != nullptr && _handle != INVALID_HANDLE_VALUE;
    }

    HANDLE Get() const {
        return _handle;
    }
};
