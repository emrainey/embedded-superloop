#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Meters unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Meters unit of measurement
/// This class provides type safety and unit-specific operations for Meters
/// stored as float with a power of 1.
class Meters : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Meters()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Meters(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Meters(Meters const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Meters& operator=(Meters& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Meters& operator=(Meters const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Meters& operator=(Meters volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Meters& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Meters volatile& operator=(Meters const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Meters volatile& operator=(Meters volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Meters
    friend constexpr inline Meters operator+(Meters const& lhs, Meters const& rhs) {
        return Meters{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Meters
    friend constexpr inline Meters operator-(Meters const& lhs, Meters const& rhs) {
        return Meters{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Meters with scalar
    friend constexpr inline Meters operator*(Meters const& lhs, float rhs) {
        return Meters{lhs.value() * rhs};
    }

    /// @brief Division operator for Meters with scalar
    friend constexpr inline Meters operator/(Meters const& lhs, float rhs) {
        return Meters{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Meters
    friend constexpr inline Meters operator*(float lhs, Meters const& rhs) {
        return Meters{lhs * rhs.value()};
    }

    /// @brief Negation operator for Meters
    friend constexpr inline Meters operator-(Meters const& other) {
        return Meters{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Meters
    friend constexpr inline bool operator==(Meters const& lhs, Meters const& rhs) {
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

    /// @brief Inequality operator for Meters
    friend constexpr inline bool operator!=(Meters const& lhs, Meters const& rhs) {
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

    /// @brief Less than operator for Meters
    friend constexpr inline bool operator<(Meters const& lhs, Meters const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Meters
    friend constexpr inline bool operator<=(Meters const& lhs, Meters const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Meters
    friend constexpr inline bool operator>(Meters const& lhs, Meters const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Meters
    friend constexpr inline bool operator>=(Meters const& lhs, Meters const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Meters
inline std::ostream& operator<<(std::ostream& os, Meters const& v) {
        os << "Meters" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
