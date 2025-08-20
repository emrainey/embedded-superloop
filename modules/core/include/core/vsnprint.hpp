#ifndef CORE_VSNPRINT_HPP_
#define CORE_VSNPRINT_HPP_

/// @file
/// The Print Interface

#include <cinttypes>
#include <cstdarg>
#include "compiler.hpp"

#ifndef PRIz
/// The format specifier for size_t
/// @note This is a workaround for the fact that size_t is not defined in the C++ standard library
#define PRIz "zu"
#endif

namespace core {

/// @brief Primitive String Formatting function from variable argument list
/// Supports %s, %d, %i, %u, %x, %p, %b (binary), %f for float ONLY (no doubles!)
/// @param buffer The buffer to form the string in
/// @param buffer_size The capacity length of the buffer
/// @param format The format string.
/// @param args The variable arguments list
unsigned long vsnprint(char buffer[], size_t buffer_size, const char* format, va_list args);

}    // namespace core

#endif    // CORE_VSNPRINT_HPP_
