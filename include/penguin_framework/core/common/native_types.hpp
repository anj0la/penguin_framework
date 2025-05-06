#pragma once

struct NativeWindowPtr {
    void* ptr;

    explicit NativeWindowPtr(void* p) : ptr(p) {}

    template <typename T>
    T* as() const {
        return static_cast<T*>(ptr);
    }
};

struct NativeRendererPtr {
    void* ptr;

    explicit NativeRendererPtr(void* p) : ptr(p) {}

    template <typename T>
    T* as() const {
        return static_cast<T*>(ptr);
    }
};

struct NativeTexturePtr {
    void* ptr;

    explicit NativeTexturePtr(void* p) : ptr(p) {}

    template <typename T>
    T* as() const {
        return static_cast<T*>(ptr);
    }
};