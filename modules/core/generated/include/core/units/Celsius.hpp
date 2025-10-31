#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Celsius unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Celsius unit of measurement
/// This class provides type safety and unit-specific operations for Celsius
/// stored as float with a power of 1.
class Celsius : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Celsius()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Celsius(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Celsius(Celsius const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Celsius& operator=(Celsius& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Celsius& operator=(Celsius const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Celsius& operator=(Celsius volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Celsius& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Celsius volatile& operator=(Celsius const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Celsius volatile& operator=(Celsius volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Celsius
    friend constexpr inline Celsius operator+(Celsius const& lhs, Celsius const& rhs) {
        return Celsius{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Celsius
    friend constexpr inline Celsius operator-(Celsius const& lhs, Celsius const& rhs) {
        return Celsius{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Celsius with scalar
    friend constexpr inline Celsius operator*(Celsius const& lhs, float rhs) {
        return Celsius{lhs.value() * rhs};
    }

    /// @brief Division operator for Celsius with scalar
    friend constexpr inline Celsius operator/(Celsius const& lhs, float rhs) {
        return Celsius{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Celsius
    friend constexpr inline Celsius operator*(float lhs, Celsius const& rhs) {
        return Celsius{lhs * rhs.value()};
    }

    /// @brief Negation operator for Celsius
    friend constexpr inline Celsius operator-(Celsius const& other) {
        return Celsius{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Celsius
    friend constexpr inline bool operator==(Celsius const& lhs, Celsius const& rhs) {
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

    /// @brief Inequality operator for Celsius
    friend constexpr inline bool operator!=(Celsius const& lhs, Celsius const& rhs) {
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

    /// @brief Less than operator for Celsius
    friend constexpr inline bool operator<(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Celsius
    friend constexpr inline bool operator<=(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Celsius
    friend constexpr inline bool operator>(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Celsius
    friend constexpr inline bool operator>=(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Celsius
inline std::ostream& operator<<(std::ostream& os, Celsius const& v) {
        os << "Celsius" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
