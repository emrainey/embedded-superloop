#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Ticks unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Ticks unit of measurement
/// This class provides type safety and unit-specific operations for Ticks
/// stored as uint32_t with a power of 1.
class Ticks : public Unit<uint32_t, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<uint32_t, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Ticks()
        : Unit<uint32_t, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Ticks(uint32_t v)
        : Unit<uint32_t, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Ticks(Ticks const& other)
        : Unit<uint32_t, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Ticks& operator=(Ticks& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Ticks& operator=(Ticks const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Ticks& operator=(Ticks volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Ticks& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Ticks volatile& operator=(Ticks const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Ticks volatile& operator=(Ticks volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Ticks
    friend constexpr inline Ticks operator+(Ticks const& lhs, Ticks const& rhs) {
        return Ticks{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Ticks
    friend constexpr inline Ticks operator-(Ticks const& lhs, Ticks const& rhs) {
        return Ticks{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Ticks with scalar
    friend constexpr inline Ticks operator*(Ticks const& lhs, uint32_t rhs) {
        return Ticks{lhs.value() * rhs};
    }

    /// @brief Division operator for Ticks with scalar
    friend constexpr inline Ticks operator/(Ticks const& lhs, uint32_t rhs) {
        return Ticks{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Ticks
    friend constexpr inline Ticks operator*(uint32_t lhs, Ticks const& rhs) {
        return Ticks{lhs * rhs.value()};
    }

    /// @brief Negation operator for Ticks
    friend constexpr inline Ticks operator-(Ticks const& other) {
        return Ticks{other.value() * static_cast<uint32_t>(-1)};
    }

    /// @brief Equality operator for Ticks
    friend constexpr inline bool operator==(Ticks const& lhs, Ticks const& rhs) {
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

    /// @brief Inequality operator for Ticks
    friend constexpr inline bool operator!=(Ticks const& lhs, Ticks const& rhs) {
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

    /// @brief Less than operator for Ticks
    friend constexpr inline bool operator<(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Ticks
    friend constexpr inline bool operator<=(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Ticks
    friend constexpr inline bool operator>(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Ticks
    friend constexpr inline bool operator>=(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Ticks
inline std::ostream& operator<<(std::ostream& os, Ticks const& v) {
        os << "Ticks" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
