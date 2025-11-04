#pragma once

struct NativePtr {
    void* ptr;

    explicit NativePtr(void* p) : ptr(p) {}

    template <typename T>
    T* as() const {
        return static_cast<T*>(ptr);
    }
};

using NativeWindowPtr = NativePtr;
using NativeRendererPtr = NativePtr;
using NativeTexturePtr = NativePtr;
using NativeTextContextPtr = NativePtr;
using NativeTextPtr = NativePtr;
using NativeFontPtr = NativePtr;
using NativeEventPtr = NativePtr;
