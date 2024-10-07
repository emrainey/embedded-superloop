#ifndef CORE_UNITS_UNIT_HPP
#define CORE_UNITS_UNIT_HPP

#include <type_traits>
#include <cstdint>

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

    /// @brief Get the value of the unit (normal)
    constexpr STORAGE_TYPE& value() { return value_; }
    /// @brief Get the value of the unit (const)
    constexpr STORAGE_TYPE const& value() const { return value_; }
    /// @brief Get the value of the unit (volatile)
    constexpr STORAGE_TYPE volatile& value() volatile { return value_; }
    /// @brief Get the value of the unit (const volatile)
    constexpr STORAGE_TYPE const volatile& value() const volatile { return value_; }
    /// @brief Get the value of the unit via explicit casting (normal)
    constexpr explicit operator STORAGE_TYPE(void) { return value_; }
    /// @brief Get the value of the unit via explicit casting (const)
    constexpr explicit operator STORAGE_TYPE(void) const { return value_; }
    /// @brief Get the value of the unit via explicit casting (volatile)
    constexpr explicit operator STORAGE_TYPE(void) volatile { return value_; }
    /// @brief Get the value of the unit via explicit casting (volatile)
    constexpr explicit operator STORAGE_TYPE(void) const volatile { return value_; }
    /// Returns the Power of the Unit
    constexpr std::size_t power() const { return power_; }

protected:
    /// @brief Default constructor
    constexpr Unit()
        : Unit(0) {}
    /// @brief Construct a new Unit object, but only for derived classes
    /// @param v The value of the unit
    constexpr explicit Unit(STORAGE_TYPE v)
        : value_{v} {}
    constexpr Unit(Unit& other)
        : value_{other.value()} {}
    constexpr Unit(Unit const& other)
        : value_{other.value()} {}
    constexpr Unit(Unit volatile& other)
        : value_{other.value()} {}
    constexpr Unit(Unit const volatile& other)
        : value_{other.value()} {}
    STORAGE_TYPE value_;
    std::size_t power_{POWER};
};

}    // namespace units
}    // namespace core

#endif    // CORE_UNITS_UNIT_HPP