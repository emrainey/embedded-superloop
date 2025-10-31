#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Degrees unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Degrees unit of measurement
/// This class provides type safety and unit-specific operations for Degrees
/// stored as float with a power of 1.
class Degrees : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Degrees()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Degrees(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Degrees(Degrees const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Degrees& operator=(Degrees& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Degrees& operator=(Degrees const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Degrees& operator=(Degrees volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Degrees& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Degrees volatile& operator=(Degrees const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Degrees volatile& operator=(Degrees volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Degrees
    friend constexpr inline Degrees operator+(Degrees const& lhs, Degrees const& rhs) {
        return Degrees{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Degrees
    friend constexpr inline Degrees operator-(Degrees const& lhs, Degrees const& rhs) {
        return Degrees{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Degrees with scalar
    friend constexpr inline Degrees operator*(Degrees const& lhs, float rhs) {
        return Degrees{lhs.value() * rhs};
    }

    /// @brief Division operator for Degrees with scalar
    friend constexpr inline Degrees operator/(Degrees const& lhs, float rhs) {
        return Degrees{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Degrees
    friend constexpr inline Degrees operator*(float lhs, Degrees const& rhs) {
        return Degrees{lhs * rhs.value()};
    }

    /// @brief Negation operator for Degrees
    friend constexpr inline Degrees operator-(Degrees const& other) {
        return Degrees{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Degrees
    friend constexpr inline bool operator==(Degrees const& lhs, Degrees const& rhs) {
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

    /// @brief Inequality operator for Degrees
    friend constexpr inline bool operator!=(Degrees const& lhs, Degrees const& rhs) {
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

    /// @brief Less than operator for Degrees
    friend constexpr inline bool operator<(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Degrees
    friend constexpr inline bool operator<=(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Degrees
    friend constexpr inline bool operator>(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Degrees
    friend constexpr inline bool operator>=(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Degrees
inline std::ostream& operator<<(std::ostream& os, Degrees const& v) {
        os << "Degrees" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
