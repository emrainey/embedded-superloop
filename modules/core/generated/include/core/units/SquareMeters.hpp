#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the SquareMeters unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the SquareMeters unit of measurement
/// This class provides type safety and unit-specific operations for SquareMeters
/// stored as float with a power of 2.
class SquareMeters : public Unit<float, 2> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<float, 2>::Type;

    /// @brief Default constructor initializing the unit
    constexpr SquareMeters()
        : Unit<float, 2>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit SquareMeters(float v)
        : Unit<float, 2>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr SquareMeters(SquareMeters const& other)
        : Unit<float, 2>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr SquareMeters& operator=(SquareMeters& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr SquareMeters& operator=(SquareMeters const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline SquareMeters& operator=(SquareMeters volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(SquareMeters& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline SquareMeters volatile& operator=(SquareMeters const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline SquareMeters volatile& operator=(SquareMeters volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for SquareMeters
    friend constexpr inline SquareMeters operator+(SquareMeters const& lhs, SquareMeters const& rhs) {
        return SquareMeters{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for SquareMeters
    friend constexpr inline SquareMeters operator-(SquareMeters const& lhs, SquareMeters const& rhs) {
        return SquareMeters{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for SquareMeters with scalar
    friend constexpr inline SquareMeters operator*(SquareMeters const& lhs, float rhs) {
        return SquareMeters{lhs.value() * rhs};
    }

    /// @brief Division operator for SquareMeters with scalar
    friend constexpr inline SquareMeters operator/(SquareMeters const& lhs, float rhs) {
        return SquareMeters{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with SquareMeters
    friend constexpr inline SquareMeters operator*(float lhs, SquareMeters const& rhs) {
        return SquareMeters{lhs * rhs.value()};
    }

    /// @brief Negation operator for SquareMeters
    friend constexpr inline SquareMeters operator-(SquareMeters const& other) {
        return SquareMeters{other.value() * static_cast<float>(-1)};
    }

    /// @brief Equality operator for SquareMeters
    friend constexpr inline bool operator==(SquareMeters const& lhs, SquareMeters const& rhs) {
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

    /// @brief Inequality operator for SquareMeters
    friend constexpr inline bool operator!=(SquareMeters const& lhs, SquareMeters const& rhs) {
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

    /// @brief Less than operator for SquareMeters
    friend constexpr inline bool operator<(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for SquareMeters
    friend constexpr inline bool operator<=(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for SquareMeters
    friend constexpr inline bool operator>(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for SquareMeters
    friend constexpr inline bool operator>=(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for SquareMeters
inline std::ostream& operator<<(std::ostream& os, SquareMeters const& v) {
        os << "SquareMeters" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
