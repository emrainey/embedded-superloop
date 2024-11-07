#ifndef CORE_STD_HPP
#define CORE_STD_HPP

#include <cstdint>
#include <cstddef>

#if not defined(UNITTEST)
// C++ Requires some global symbols defined in order to compile.
extern "C" void __cxa_pure_virtual(void);

/// Placement new operator given pointer
/// @note Required for C++ Compatibility
void *operator new(std::size_t bytes, void *pointer) noexcept;

/// Placement new operator given address
/// @note _NOT_ Required for C++ Compatibility (customized for device-as-object)
void *operator new(std::size_t bytes, std::uintptr_t address) noexcept;
#endif

#endif    // CORE_STD_HPP
