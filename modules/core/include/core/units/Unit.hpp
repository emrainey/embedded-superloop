#ifndef CORE_UNITS_UNIT_HPP
#define CORE_UNITS_UNIT_HPP

#include <cstdint>
#include <type_traits>

#if defined(UNITTEST)
#include <iostream>
#endif

namespace core {
namespace units {

/// @brief The basic storage unit
/// @tparam STORAGE_TYPE
template <typename STORAGE_TYPE, std::size_t POWER = 1U>
class Unit {
public:
    static_assert(std::is_floating_point<STORAGE_TYPE>::value or std::is_integral<STORAGE_TYPE>::value, "Must be a floating point type or integral");
    using Type = STORAGE_TYPE;    ///< The type of the unit

    /// @brief Get the value of the unit (normal)
    constexpr Type& value() { return value_; }
    /// @brief Get the value of the unit (const)
    constexpr Type const& value() const { return value_; }
    /// @brief Get the value of the unit (volatile)
    constexpr Type volatile& value() volatile { return value_; }
    /// @brief Get the value of the unit (const volatile)
    constexpr Type const volatile& value() const volatile { return value_; }
    /// @brief Get the value of the unit via explicit casting (normal)
    constexpr explicit operator Type(void) { return value_; }
    /// @brief Get the value of the unit via explicit casting (const)
    constexpr explicit operator Type(void) const { return value_; }
    /// @brief Get the value of the unit via explicit casting (volatile)
    constexpr explicit operator Type(void) volatile { return value_; }
    /// @brief Get the value of the unit via explicit casting (const volatile)
    constexpr explicit operator Type(void) const volatile { return value_; }
    /// Returns the Power of the Unit
    constexpr std::size_t power() const { return power_; }

protected:
    /// @brief Default constructor
    constexpr Unit()
        : Unit(0) {}
    /// @brief Construct a new Unit object, but only for derived classes
    /// @param v The value of the unit
    constexpr explicit Unit(Type v)
        : value_{POWER == 0u ? static_cast<Type>(1) : v} {}
    /// @brief The copy constructor
    /// @param other The other const value
    constexpr Unit(Unit const& other)
        : value_{other.value()} {}
    /// @brief The copy constructor
    /// @param other The other volatile value
    constexpr Unit(Unit volatile& other)
        : value_{other.value()} {}
    /// @brief The copy constructor
    /// @param other The other const volatile value
    constexpr Unit(Unit const volatile& other)
        : value_{other.value()} {}

    Type value_;                  ///< The value of the unit
    std::size_t power_{POWER};    ///< The power of the unit (can not be zero)
};

}    // namespace units
}    // namespace core

#endif    // CORE_UNITS_UNIT_HPP
