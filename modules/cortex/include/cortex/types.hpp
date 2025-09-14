#ifndef CORTEX_M_TYPES_HPP_
#define CORTEX_M_TYPES_HPP_

/// @file
/// The Cortex Microcontroller Core Header

#include <cstddef>
#include <cstdint>
#include <limits>
#include "compiler.hpp"

#include "core/Units.hpp"

namespace cortex {

/// Clocks are measured in Hertz
using Hertz = core::units::Hertz;
using core::units::operator""_Hz;
using core::units::operator""_KHz;
using core::units::operator""_MHz;

/// The bit layout of an IEEE-754 Single Precision Floating Point number.
struct SinglePrecision final {
    std::uint32_t mantissa : 23U;
    std::uint32_t exponent : 8U;
    std::uint32_t sign     : 1U;
};
#if defined(__arm__)
static_assert(sizeof(SinglePrecision) == sizeof(float), "Must be the same size");
#endif
static_assert(std::numeric_limits<float>::is_iec559, "Must be IEEE-754 compliant");

// let's enforce some assumptions about the platform
static_assert(sizeof(char) == 1U, "Must be this size");
static_assert(sizeof(std::int8_t) == 1U, "Must be this size");
static_assert(sizeof(std::uint8_t) == 1U, "Must be this size");
static_assert(sizeof(std::int16_t) == 2U, "Must be this size");
static_assert(sizeof(std::uint16_t) == 2U, "Must be this size");
static_assert(sizeof(std::int32_t) == 4U, "Must be this size");
static_assert(sizeof(std::uint32_t) == 4U, "Must be this size");

#if defined(__arm__)
static_assert(sizeof(std::size_t) == 4U, "Must be this size");
static_assert(sizeof(void*) == 4U, "Must be this size");
static_assert(sizeof(std::uintptr_t) == 4U, "Must be this size");
#endif

static_assert(alignof(char) == 1U, "Must be this alignment");
static_assert(alignof(std::int8_t) == 1U, "Must be this alignment");
static_assert(alignof(std::uint8_t) == 1U, "Must be this alignment");
static_assert(alignof(std::int16_t) == 2U, "Must be this alignment");
static_assert(alignof(std::uint16_t) == 2U, "Must be this alignment");
static_assert(alignof(std::int32_t) == 4U, "Must be this alignment");
static_assert(alignof(std::uint32_t) == 4U, "Must be this alignment");
#if defined(__arm__)
static_assert(alignof(std::size_t) == 4U, "Must be this alignment");
static_assert(alignof(void*) == 4U, "Must be this alignment");
static_assert(alignof(std::uintptr_t) == 4U, "Must be this alignment");
#endif

/// The hardware representation of a processor word on Cortex Microcontroller 32 bit processor.
/// Use this structure to mimic how a processor register would be used
/// to allow easy conversion between types.
/// @warning This makes platform assumptions and Compiler assumptions!
union word final {
    std::uintptr_t as_address;    ///< extract value as an address
    void* as_pointer;             ///< extract value as a pointer
    std::uint32_t as_u32;         ///< extract value as a single u32
    std::uint16_t as_u16[2];      ///< extract value as a pair of u16
    std::uint8_t as_u08[4];       ///< extract value as a quad of u08
    std::int32_t as_s32;          ///< extract value as a single s32
    std::int16_t as_s16[2];       ///< extract value as a pair of s16
    std::int8_t as_s08[4];        ///< extract value as a quad of s08
    char as_chr[4];               ///< extract value as a quad of chars
    SinglePrecision as_f32;       ///< extract value as a single precision
};
#if defined(__arm__)
static_assert(alignof(word) == 4U, "Must be exactly this alignment");
static_assert(sizeof(word) == 4U, "Must be exactly this size");
#endif

/// Converts a word to a specific pointer type with minimal fuss
/// @code {.cpp}
// Foo *ptr = as<Foo>(myword);
/// @endcode
template <typename Type>
constexpr Type* as(word const& w) {
    return reinterpret_cast<Type*>(w.as_pointer);
}

/// Holds the various modes of the Processor
namespace modes {
/// Indicates if the Process is Executing a Handler or not
enum class Execution : std::uint32_t {
    Handler = 0U,    ///< A handler is running. Handlers are in Privileged::High
    Thread = 1U,     ///< Non-handler code is running. Can be in either Privileged mode.
};

/// The Privileged Mode Enumeration
enum class Privileged : std::uint32_t {
    High = 0U,    ///< The Process is able to access resources marked as privileged
    Low = 1U,     ///< Accessing resources marked as privileged will cause a fault.
};

/// The Stack Type Enumeration
enum class Stack : std::uint32_t {
    Main = 0U,       //!< Kernel and Exceptions
    Process = 1U,    //!< Threads
};

/// The two different types of Stack Frames for exceptions
enum class Frame : std::uint32_t {
    Extended = 0U,
    Basic = 1U,
};

/// Float operations round towards
enum class Rounding : std::uint32_t {
    Nearest = 0b00,             ///< Rounds toward nearest
    PositiveInfinity = 0b01,    ///< Rounds toward +inf
    NegativeInfinity = 0b10,    ///< Rounds toward -inf
    Zero = 0b11,                ///< Rounds toward 0
};

}    // namespace modes

/// Defines a type for generic functions with no return and no parameters.
using function = void (*)(void);

/// A function pointer to a constructor function
using constructor = function;

/// A function pointer to a destructor function
using destructor = function;

}    // namespace cortex

#endif    // CORTEX_M_TYPES_HPP_
