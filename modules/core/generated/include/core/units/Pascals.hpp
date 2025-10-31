#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Pascals unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Pascals unit of measurement
/// This class provides type safety and unit-specific operations for Pascals
/// stored as float with a power of 1.
class Pascals : public Unit<float, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Pascals()
        : Unit<float, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Pascals(float v)
        : Unit<float, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Pascals(Pascals const& other)
        : Unit<float, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Pascals& operator=(Pascals& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Pascals& operator=(Pascals const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Pascals& operator=(Pascals volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Pascals& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Pascals volatile& operator=(Pascals const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Pascals volatile& operator=(Pascals volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Pascals
    friend constexpr inline Pascals operator+(Pascals const& lhs, Pascals const& rhs) {
        return Pascals{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Pascals
    friend constexpr inline Pascals operator-(Pascals const& lhs, Pascals const& rhs) {
        return Pascals{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Pascals with scalar
    friend constexpr inline Pascals operator*(Pascals const& lhs, float rhs) {
        return Pascals{lhs.value() * rhs};
    }

    /// @brief Division operator for Pascals with scalar
    friend constexpr inline Pascals operator/(Pascals const& lhs, float rhs) {
        return Pascals{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Pascals
    friend constexpr inline Pascals operator*(float lhs, Pascals const& rhs) {
        return Pascals{lhs * rhs.value()};
    }

    /// @brief Negation operator for Pascals
    friend constexpr inline Pascals operator-(Pascals const& other) {
        return Pascals{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for Pascals
    friend constexpr inline bool operator==(Pascals const& lhs, Pascals const& rhs) {
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

    /// @brief Inequality operator for Pascals
    friend constexpr inline bool operator!=(Pascals const& lhs, Pascals const& rhs) {
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

    /// @brief Less than operator for Pascals
    friend constexpr inline bool operator<(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Pascals
    friend constexpr inline bool operator<=(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Pascals
    friend constexpr inline bool operator>(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Pascals
    friend constexpr inline bool operator>=(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Pascals
inline std::ostream& operator<<(std::ostream& os, Pascals const& v) {
        os << "Pascals" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
