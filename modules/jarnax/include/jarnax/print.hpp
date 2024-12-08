#ifndef JARNAX_PRINT_HPP_
#define JARNAX_PRINT_HPP_

/// @file
/// The Print Interface

#include "compiler.hpp"
#include <cinttypes>

#ifndef PRIz
#define PRIz "zu"
#endif

/// The namespace of the system level functions
namespace jarnax {

/// @brief Primitive Printing Facility.
/// Supports %s, %d, %i, %u, %x, %b (binary), %f for float ONLY.
/// @param format The format string.
/// @param ... The variadic arguments.
void print(const char* format, ...) ATTRIBUTE((format(printf, 1, 2)));

}    // namespace jarnax

#endif    // JARNAX_PRINT_HPP_
