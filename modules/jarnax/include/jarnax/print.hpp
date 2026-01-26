#ifndef JARNAX_PRINT_HPP_
#define JARNAX_PRINT_HPP_

/// @file
/// The Print Interface

#include <cinttypes>
#include <cstdarg>
#include "compiler.hpp"
#include "core/Printer.hpp"
#include "core/Span.hpp"
#include "debug.hpp"

#ifndef PRIz
/// The format specifier for size_t
/// @note This is a workaround for the fact that size_t is not defined in the C++ standard library
#define PRIz "zu"
#endif

/// The namespace of the system level functions
namespace jarnax {

constexpr static bool use_rtt_for_printf = true;
constexpr static bool use_swo_for_printf = false;
constexpr static bool use_uart_for_printf = false;
constexpr static bool use_logger_for_printf = false;
constexpr static bool use_system_printf =
#if defined(UNITTEST)
    true;    ///< For UNITTEST
#else
    false;    ///< For normal operation
#endif

/// @brief Primitive Printing Facility.
/// Supports %s, %d, %i, %u, %x, %b (binary), %f for float ONLY.
/// @param format The format string.
/// @param ... The variadic arguments.
void print(const char* format, ...) ATTRIBUTE((format(printf, 1, 2)));

/// @brief Prints the information of a status object
/// @param source Some literal string to identify the source of the status
/// @param status The status object to print
void print(char const* const source, core::Status status);

/// @brief Primitive Printing Facility.
/// Supports %s, %d, %i, %u, %x, %p, %b (binary), %f for float ONLY (no doubles!)
/// @param format The format string.
/// @param ... The variadic arguments.
void print(const char* format, ...) ATTRIBUTE((format(printf, 1, 2)));

/// @brief Primitive String Formatting function from variable argument list
/// Supports %s, %d, %i, %u, %x, %p, %b (binary), %f for float ONLY (no doubles!)
/// @param buffer The buffer to form the string in
/// @param buffer_size The capacity length of the buffer
/// @param format The format string.
/// @param args The variable arguments list
unsigned long vsnprint(char buffer[], size_t buffer_size, const char* format, va_list args);

/// Prints a span of values in hex format with prefix
/// @tparam T The type of elements in the span
/// @param prefix The prefix string to print
/// @param span The span of data to print
template <typename T>
void print(char const* const prefix, core::Span<T> const& span) {
    print("%s span: %p:%zu\r\n", prefix, span.data(), span.count());
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
