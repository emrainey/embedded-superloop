#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Ohms unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Ohms unit of measurement
/// This class provides type safety and unit-specific operations for Ohms
/// stored as float with a power of 1.
class Ohms : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Ohms()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Ohms(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Ohms(Ohms const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Ohms& operator=(Ohms& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Ohms& operator=(Ohms const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Ohms& operator=(Ohms volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Ohms& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Ohms volatile& operator=(Ohms const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Ohms volatile& operator=(Ohms volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Ohms
    friend constexpr inline Ohms operator+(Ohms const& lhs, Ohms const& rhs) {
        return Ohms{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Ohms
    friend constexpr inline Ohms operator-(Ohms const& lhs, Ohms const& rhs) {
        return Ohms{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Ohms with scalar
    friend constexpr inline Ohms operator*(Ohms const& lhs, float rhs) {
        return Ohms{lhs.value() * rhs};
    }

    /// @brief Division operator for Ohms with scalar
    friend constexpr inline Ohms operator/(Ohms const& lhs, float rhs) {
        return Ohms{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Ohms
    friend constexpr inline Ohms operator*(float lhs, Ohms const& rhs) {
        return Ohms{lhs * rhs.value()};
    }

    /// @brief Negation operator for Ohms
    friend constexpr inline Ohms operator-(Ohms const& other) {
        return Ohms{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Ohms
    friend constexpr inline bool operator==(Ohms const& lhs, Ohms const& rhs) {
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

    /// @brief Inequality operator for Ohms
    friend constexpr inline bool operator!=(Ohms const& lhs, Ohms const& rhs) {
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

    /// @brief Less than operator for Ohms
    friend constexpr inline bool operator<(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Ohms
    friend constexpr inline bool operator<=(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Ohms
    friend constexpr inline bool operator>(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Ohms
    friend constexpr inline bool operator>=(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Ohms
inline std::ostream& operator<<(std::ostream& os, Ohms const& v) {
        os << "Ohms" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
