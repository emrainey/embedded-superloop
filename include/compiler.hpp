#ifndef COMPILER_HPP_
#define COMPILER_HPP_

#include <concepts>

/// @file
/// Contains compiler specific attributes and macros. These should be the only MACROS in the system

#if defined(UNITTEST)
#define ATTRIBUTE(x)
#define LINKER_SECTION(x)
#define NAKED
#define USED
#define ALWAYS_INLINE
#else
#define ATTRIBUTE(x) __attribute__(x)
#define LINKER_SECTION(x) __attribute__((used, section(x)))
#define NAKED __attribute__((used, naked))
#define USED __attribute__((used))
#define ALWAYS_INLINE __attribute__((always_inline))
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