#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the MicroSeconds unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the MicroSeconds unit of measurement
/// This class provides type safety and unit-specific operations for MicroSeconds
/// stored as uint64_t with a power of 1.
class MicroSeconds : public Unit<uint64_t, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<uint64_t, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr MicroSeconds()
        : Unit<uint64_t, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit MicroSeconds(uint64_t v)
        : Unit<uint64_t, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr MicroSeconds(MicroSeconds const& other)
        : Unit<uint64_t, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr MicroSeconds& operator=(MicroSeconds& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr MicroSeconds& operator=(MicroSeconds const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline MicroSeconds& operator=(MicroSeconds volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(MicroSeconds& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline MicroSeconds volatile& operator=(MicroSeconds const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline MicroSeconds volatile& operator=(MicroSeconds volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for MicroSeconds
    friend constexpr inline MicroSeconds operator+(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return MicroSeconds{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for MicroSeconds
    friend constexpr inline MicroSeconds operator-(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return MicroSeconds{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for MicroSeconds with scalar
    friend constexpr inline MicroSeconds operator*(MicroSeconds const& lhs, uint64_t rhs) {
        return MicroSeconds{lhs.value() * rhs};
    }

    /// @brief Division operator for MicroSeconds with scalar
    friend constexpr inline MicroSeconds operator/(MicroSeconds const& lhs, uint64_t rhs) {
        return MicroSeconds{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with MicroSeconds
    friend constexpr inline MicroSeconds operator*(uint64_t lhs, MicroSeconds const& rhs) {
        return MicroSeconds{lhs * rhs.value()};
    }

    /// @brief Negation operator for MicroSeconds
    friend constexpr inline MicroSeconds operator-(MicroSeconds const& other) {
        return MicroSeconds{other.value() * static_cast<uint64_t>(-1)};
    }

    /// @brief Equality operator for MicroSeconds
    friend constexpr inline bool operator==(MicroSeconds const& lhs, MicroSeconds const& rhs) {
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

    /// @brief Inequality operator for MicroSeconds
    friend constexpr inline bool operator!=(MicroSeconds const& lhs, MicroSeconds const& rhs) {
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

    /// @brief Less than operator for MicroSeconds
    friend constexpr inline bool operator<(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for MicroSeconds
    friend constexpr inline bool operator<=(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for MicroSeconds
    friend constexpr inline bool operator>(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for MicroSeconds
    friend constexpr inline bool operator>=(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for MicroSeconds
inline std::ostream& operator<<(std::ostream& os, MicroSeconds const& v) {
        os << "MicroSeconds" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
