#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Watts unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Watts unit of measurement
/// This class provides type safety and unit-specific operations for Watts
/// stored as float with a power of 1.
class Watts : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Watts()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Watts(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Watts(Watts const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Watts& operator=(Watts& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Watts& operator=(Watts const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Watts& operator=(Watts volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Watts& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Watts volatile& operator=(Watts const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Watts volatile& operator=(Watts volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Watts
    friend constexpr inline Watts operator+(Watts const& lhs, Watts const& rhs) {
        return Watts{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Watts
    friend constexpr inline Watts operator-(Watts const& lhs, Watts const& rhs) {
        return Watts{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Watts with scalar
    friend constexpr inline Watts operator*(Watts const& lhs, float rhs) {
        return Watts{lhs.value() * rhs};
    }

    /// @brief Division operator for Watts with scalar
    friend constexpr inline Watts operator/(Watts const& lhs, float rhs) {
        return Watts{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Watts
    friend constexpr inline Watts operator*(float lhs, Watts const& rhs) {
        return Watts{lhs * rhs.value()};
    }

    /// @brief Negation operator for Watts
    friend constexpr inline Watts operator-(Watts const& other) {
        return Watts{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Watts
    friend constexpr inline bool operator==(Watts const& lhs, Watts const& rhs) {
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

    /// @brief Inequality operator for Watts
    friend constexpr inline bool operator!=(Watts const& lhs, Watts const& rhs) {
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

    /// @brief Less than operator for Watts
    friend constexpr inline bool operator<(Watts const& lhs, Watts const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Watts
    friend constexpr inline bool operator<=(Watts const& lhs, Watts const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Watts
    friend constexpr inline bool operator>(Watts const& lhs, Watts const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Watts
    friend constexpr inline bool operator>=(Watts const& lhs, Watts const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Watts
inline std::ostream& operator<<(std::ostream& os, Watts const& v) {
        os << "Watts" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
