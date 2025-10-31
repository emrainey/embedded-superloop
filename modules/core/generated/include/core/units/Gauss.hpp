#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Gauss unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Gauss unit of measurement
/// This class provides type safety and unit-specific operations for Gauss
/// stored as float with a power of 1.
class Gauss : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Gauss()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Gauss(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Gauss(Gauss const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Gauss& operator=(Gauss& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Gauss& operator=(Gauss const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Gauss& operator=(Gauss volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Gauss& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Gauss volatile& operator=(Gauss const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Gauss volatile& operator=(Gauss volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Gauss
    friend constexpr inline Gauss operator+(Gauss const& lhs, Gauss const& rhs) {
        return Gauss{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Gauss
    friend constexpr inline Gauss operator-(Gauss const& lhs, Gauss const& rhs) {
        return Gauss{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Gauss with scalar
    friend constexpr inline Gauss operator*(Gauss const& lhs, float rhs) {
        return Gauss{lhs.value() * rhs};
    }

    /// @brief Division operator for Gauss with scalar
    friend constexpr inline Gauss operator/(Gauss const& lhs, float rhs) {
        return Gauss{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Gauss
    friend constexpr inline Gauss operator*(float lhs, Gauss const& rhs) {
        return Gauss{lhs * rhs.value()};
    }

    /// @brief Negation operator for Gauss
    friend constexpr inline Gauss operator-(Gauss const& other) {
        return Gauss{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Gauss
    friend constexpr inline bool operator==(Gauss const& lhs, Gauss const& rhs) {
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

    /// @brief Inequality operator for Gauss
    friend constexpr inline bool operator!=(Gauss const& lhs, Gauss const& rhs) {
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

    /// @brief Less than operator for Gauss
    friend constexpr inline bool operator<(Gauss const& lhs, Gauss const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Gauss
    friend constexpr inline bool operator<=(Gauss const& lhs, Gauss const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Gauss
    friend constexpr inline bool operator>(Gauss const& lhs, Gauss const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Gauss
    friend constexpr inline bool operator>=(Gauss const& lhs, Gauss const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Gauss
inline std::ostream& operator<<(std::ostream& os, Gauss const& v) {
        os << "Gauss" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
