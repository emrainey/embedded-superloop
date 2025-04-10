#include "core/core.hpp"

extern "C" void __cxa_pure_virtual(void) {
    while (true) {
    }
}

extern "C" int atexit(void (*function)(void)) {
    (void)function;
    return 0;
}

extern "C" void __cxa_atexit(void (*function)(void *), void *parameter, void *dso_handle) {
    (void)function;
    (void)parameter;
    (void)dso_handle;
}

/// @fn __cxa_guard_acquire
/// This is called when the compiler is trying to make sure that
/// an object is constructed before being used (typically in a threading environment).
/// In this single-threaded system, this does not need to be defined.
/// @note Use `-fno-threadsafe-statics` in GCC to disable the need for this function.
extern "C" void __cxa_guard_acquire();