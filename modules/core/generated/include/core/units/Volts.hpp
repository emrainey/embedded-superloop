#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Volts unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Volts unit of measurement
/// This class provides type safety and unit-specific operations for Volts
/// stored as float with a power of 1.
class Volts : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Volts()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Volts(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Volts(Volts const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Volts& operator=(Volts& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Volts& operator=(Volts const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Volts& operator=(Volts volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Volts& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Volts volatile& operator=(Volts const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Volts volatile& operator=(Volts volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Volts
    friend constexpr inline Volts operator+(Volts const& lhs, Volts const& rhs) {
        return Volts{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Volts
    friend constexpr inline Volts operator-(Volts const& lhs, Volts const& rhs) {
        return Volts{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Volts with scalar
    friend constexpr inline Volts operator*(Volts const& lhs, float rhs) {
        return Volts{lhs.value() * rhs};
    }

    /// @brief Division operator for Volts with scalar
    friend constexpr inline Volts operator/(Volts const& lhs, float rhs) {
        return Volts{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Volts
    friend constexpr inline Volts operator*(float lhs, Volts const& rhs) {
        return Volts{lhs * rhs.value()};
    }

    /// @brief Negation operator for Volts
    friend constexpr inline Volts operator-(Volts const& other) {
        return Volts{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Volts
    friend constexpr inline bool operator==(Volts const& lhs, Volts const& rhs) {
        if constexpr (std::is_floating_point_v<float>) {
            return std::fabs(lhs.value() - rhs.value()) < std::numeric_limits<float>::epsilon();
        } else {
            #if defined(__clang__)
            #pragma clang diagnostic push
            #pragma clang diagnostic ignored "-Wfloat-equal"
            #endif
            return lhs.value() == rhs.value();
            #if defined(__clang__)
            #pragma clang diagnostic pop
            #endif
        }
    }

    /// @brief Inequality operator for Volts
    friend constexpr inline bool operator!=(Volts const& lhs, Volts const& rhs) {
        if constexpr (std::is_floating_point_v<float>) {
            return std::fabs(lhs.value() - rhs.value()) >= std::numeric_limits<float>::epsilon();
        } else {
            #if defined(__clang__)
            #pragma clang diagnostic push
            #pragma clang diagnostic ignored "-Wfloat-equal"
            #endif
            return lhs.value() != rhs.value();
            #if defined(__clang__)
            #pragma clang diagnostic pop
            #endif
        }
    }

    /// @brief Less than operator for Volts
    friend constexpr inline bool operator<(Volts const& lhs, Volts const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Volts
    friend constexpr inline bool operator<=(Volts const& lhs, Volts const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Volts
    friend constexpr inline bool operator>(Volts const& lhs, Volts const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Volts
    friend constexpr inline bool operator>=(Volts const& lhs, Volts const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Volts
inline std::ostream& operator<<(std::ostream& os, Volts const& v) {
        os << "Volts" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
