#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Iota unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Iota unit of measurement
/// This class provides type safety and unit-specific operations for Iota
/// stored as uint64_t with a power of 1.
class Iota : public Unit<uint64_t, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<uint64_t, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Iota()
        : Unit<uint64_t, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Iota(uint64_t v)
        : Unit<uint64_t, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Iota(Iota const& other)
        : Unit<uint64_t, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Iota& operator=(Iota& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Iota& operator=(Iota const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Iota& operator=(Iota volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Iota& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Iota volatile& operator=(Iota const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Iota volatile& operator=(Iota volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Iota
    friend constexpr inline Iota operator+(Iota const& lhs, Iota const& rhs) {
        return Iota{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Iota
    friend constexpr inline Iota operator-(Iota const& lhs, Iota const& rhs) {
        return Iota{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Iota with scalar
    friend constexpr inline Iota operator*(Iota const& lhs, uint64_t rhs) {
        return Iota{lhs.value() * rhs};
    }

    /// @brief Division operator for Iota with scalar
    friend constexpr inline Iota operator/(Iota const& lhs, uint64_t rhs) {
        return Iota{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Iota
    friend constexpr inline Iota operator*(uint64_t lhs, Iota const& rhs) {
        return Iota{lhs * rhs.value()};
    }

    /// @brief Negation operator for Iota
    friend constexpr inline Iota operator-(Iota const& other) {
        return Iota{other.value() * static_cast<uint64_t>(-1)};
    }

    /// @brief Equality operator for Iota
    friend constexpr inline bool operator==(Iota const& lhs, Iota const& rhs) {
        if constexpr (std::is_floating_point_v<uint64_t>) {
            return std::fabs(lhs.value() - rhs.value()) < std::numeric_limits<uint64_t>::epsilon();
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

    /// @brief Inequality operator for Iota
    friend constexpr inline bool operator!=(Iota const& lhs, Iota const& rhs) {
        if constexpr (std::is_floating_point_v<uint64_t>) {
            return std::fabs(lhs.value() - rhs.value()) >= std::numeric_limits<uint64_t>::epsilon();
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

    /// @brief Less than operator for Iota
    friend constexpr inline bool operator<(Iota const& lhs, Iota const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Iota
    friend constexpr inline bool operator<=(Iota const& lhs, Iota const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Iota
    friend constexpr inline bool operator>(Iota const& lhs, Iota const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Iota
    friend constexpr inline bool operator>=(Iota const& lhs, Iota const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Iota
inline std::ostream& operator<<(std::ostream& os, Iota const& v) {
        os << "Iota" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
