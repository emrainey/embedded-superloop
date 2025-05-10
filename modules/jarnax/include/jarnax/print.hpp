#ifndef JARNAX_PRINT_HPP_
#define JARNAX_PRINT_HPP_

/// @file
/// The Print Interface

#include "compiler.hpp"
#include <cinttypes>
#include "core/Printer.hpp"
#include "core/Span.hpp"

#ifndef PRIz
/// The format specifier for size_t
/// @note This is a workaround for the fact that size_t is not defined in the C++ standard library
#define PRIz "zu"
#endif

/// The namespace of the system level functions
namespace jarnax {

/// @brief Prints the information of a status object
/// @param source Some literal string to identify the source of the status
/// @param status The status object to print
void print(char const* const source, core::Status status);

/// @brief Primitive Printing Facility.
/// Supports %s, %d, %i, %u, %x, %p, %b (binary), %f for float ONLY (no doubles!)
/// @param format The format string.
/// @param ... The variadic arguments.
void print(const char* format, ...) ATTRIBUTE((format(printf, 1, 2)));

template <typename T>
void print(core::Span<T> const& span) {
    print("Span: %p:%zu\r\n", span.data(), span.count());
    for (size_t i = 0U; i < span.count(); i++) {
        bool is_first = ((i % 8U) == 0U);
        if (is_first) {
            if (i != 0U) {
                print("\r\n");
            }
            print("[%x]", i);
        }
        print("%hhx ", span.data()[i]);
    }
    print("\r\n");
}

}    // namespace jarnax

#endif    // JARNAX_PRINT_HPP_
