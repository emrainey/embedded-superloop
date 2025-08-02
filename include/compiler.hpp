#ifndef COMPILER_HPP_
#define COMPILER_HPP_

#include <concepts>

/// @file
/// Contains compiler specific attributes and macros. These should be the only MACROS in the system due to how the attributes are different on
/// different compilers.

#if defined(UNITTEST)
#define ATTRIBUTE(x)
#define LINKER_SECTION(x)
#define NAKED
#define USED
#define ALWAYS_INLINE
#define ISR
#else
#define ATTRIBUTE(x) __attribute__(x)
#define LINKER_SECTION(x) ATTRIBUTE((used, section(x)))
#define NAKED ATTRIBUTE((used, naked))
#define USED ATTRIBUTE((used))
#define ALWAYS_INLINE ATTRIBUTE((always_inline))
#define ISR ATTRIBUTE((used, naked, nothrow, noreturn, weak, alias("dummy_isr")))
#endif

#include <cstdint>
#include <cstddef>
#include <compare>

// clang-format off
inline size_t operator""_Z( unsigned long long int value) {
    return size_t(value);
}
// clang-format on

/// A concept that requires the type to implement all the comparison operators
template <typename TYPE>
concept Comparible = requires(std::remove_reference_t<TYPE> const& t, std::remove_reference_t<TYPE> const& u) {
    { t < u } -> std::convertible_to<bool>;
    { t <= u } -> std::convertible_to<bool>;
    { t > u } -> std::convertible_to<bool>;
    { t >= u } -> std::convertible_to<bool>;
    { t == u } -> std::convertible_to<bool>;
    { t != u } -> std::convertible_to<bool>;
    { t <=> u } -> std::convertible_to<std::strong_ordering>;
};

#endif    // COMPILER_HPP_