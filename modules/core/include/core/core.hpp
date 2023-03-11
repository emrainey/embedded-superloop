#ifndef CORE_HPP_
#define CORE_HPP_

/// @file
/// Core Library

#include <cstdint>
#include <cstddef>

#include "core/Span.hpp"
#include "core/Array.hpp"
#include "core/Split.hpp"
#include "core/Ring.hpp"
#include "core/Stack.hpp"

// C++ Requires some global symbols defined in order to compile.
extern "C" void __cxa_pure_virtual(void);

/// Placement new operator given pointer
/// @note Required for C++ Compatibility
void *operator new(std::size_t bytes, void *pointer);

/// Placement new operator given address
/// @note _NOT_ Required for C++ Compatibility (customized for device-as-object)
void *operator new(std::size_t bytes, uintptr_t address);

#endif    // CORE_HPP_