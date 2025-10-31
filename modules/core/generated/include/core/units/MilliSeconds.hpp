#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the MilliSeconds unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the MilliSeconds unit of measurement
/// This class provides type safety and unit-specific operations for MilliSeconds
/// stored as uint32_t with a power of 1.
class MilliSeconds : public Unit<uint32_t, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<uint32_t, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr MilliSeconds()
        : Unit<uint32_t, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit MilliSeconds(uint32_t v)
        : Unit<uint32_t, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr MilliSeconds(MilliSeconds const& other)
        : Unit<uint32_t, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr MilliSeconds& operator=(MilliSeconds& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr MilliSeconds& operator=(MilliSeconds const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline MilliSeconds& operator=(MilliSeconds volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(MilliSeconds& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline MilliSeconds volatile& operator=(MilliSeconds const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline MilliSeconds volatile& operator=(MilliSeconds volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for MilliSeconds
    friend constexpr inline MilliSeconds operator+(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return MilliSeconds{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for MilliSeconds
    friend constexpr inline MilliSeconds operator-(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return MilliSeconds{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for MilliSeconds with scalar
    friend constexpr inline MilliSeconds operator*(MilliSeconds const& lhs, uint32_t rhs) {
        return MilliSeconds{lhs.value() * rhs};
    }

    /// @brief Division operator for MilliSeconds with scalar
    friend constexpr inline MilliSeconds operator/(MilliSeconds const& lhs, uint32_t rhs) {
        return MilliSeconds{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with MilliSeconds
    friend constexpr inline MilliSeconds operator*(uint32_t lhs, MilliSeconds const& rhs) {
        return MilliSeconds{lhs * rhs.value()};
    }

    /// @brief Negation operator for MilliSeconds
    friend constexpr inline MilliSeconds operator-(MilliSeconds const& other) {
        return MilliSeconds{other.value() * static_cast<uint32_t>(-1)};
    }

    /// @brief Equality operator for MilliSeconds
    friend constexpr inline bool operator==(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        if constexpr (std::is_floating_point_v<uint32_t>) {
            return std::fabs(lhs.value() - rhs.value()) < std::numeric_limits<uint32_t>::epsilon();
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

    /// @brief Inequality operator for MilliSeconds
    friend constexpr inline bool operator!=(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        if constexpr (std::is_floating_point_v<uint32_t>) {
            return std::fabs(lhs.value() - rhs.value()) >= std::numeric_limits<uint32_t>::epsilon();
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

    /// @brief Less than operator for MilliSeconds
    friend constexpr inline bool operator<(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for MilliSeconds
    friend constexpr inline bool operator<=(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for MilliSeconds
    friend constexpr inline bool operator>(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for MilliSeconds
    friend constexpr inline bool operator>=(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for MilliSeconds
inline std::ostream& operator<<(std::ostream& os, MilliSeconds const& v) {
        os << "MilliSeconds" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
