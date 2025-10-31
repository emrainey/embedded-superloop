#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Seconds unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Seconds unit of measurement
/// This class provides type safety and unit-specific operations for Seconds
/// stored as float with a power of 1.
class Seconds : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Seconds()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Seconds(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Seconds(Seconds const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Seconds& operator=(Seconds& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Seconds& operator=(Seconds const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Seconds& operator=(Seconds volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Seconds& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Seconds volatile& operator=(Seconds const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Seconds volatile& operator=(Seconds volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Seconds
    friend constexpr inline Seconds operator+(Seconds const& lhs, Seconds const& rhs) {
        return Seconds{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Seconds
    friend constexpr inline Seconds operator-(Seconds const& lhs, Seconds const& rhs) {
        return Seconds{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Seconds with scalar
    friend constexpr inline Seconds operator*(Seconds const& lhs, float rhs) {
        return Seconds{lhs.value() * rhs};
    }

    /// @brief Division operator for Seconds with scalar
    friend constexpr inline Seconds operator/(Seconds const& lhs, float rhs) {
        return Seconds{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Seconds
    friend constexpr inline Seconds operator*(float lhs, Seconds const& rhs) {
        return Seconds{lhs * rhs.value()};
    }

    /// @brief Negation operator for Seconds
    friend constexpr inline Seconds operator-(Seconds const& other) {
        return Seconds{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Seconds
    friend constexpr inline bool operator==(Seconds const& lhs, Seconds const& rhs) {
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

    /// @brief Inequality operator for Seconds
    friend constexpr inline bool operator!=(Seconds const& lhs, Seconds const& rhs) {
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

    /// @brief Less than operator for Seconds
    friend constexpr inline bool operator<(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Seconds
    friend constexpr inline bool operator<=(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Seconds
    friend constexpr inline bool operator>(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Seconds
    friend constexpr inline bool operator>=(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Seconds
inline std::ostream& operator<<(std::ostream& os, Seconds const& v) {
        os << "Seconds" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
