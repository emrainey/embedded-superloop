#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Hertz unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
/// @brief Class representing the Hertz unit of measurement
/// This class provides type safety and unit-specific operations for Hertz
/// stored as uint32_t with a power of 1.
class Hertz : public Unit<uint32_t, 1> {
public:
    /// @brief The underlying storage type for the unit
    using StorageType = typename Unit<uint32_t, 1>::Type;

    /// @brief Default constructor initializing the unit
    constexpr Hertz()
        : Unit<uint32_t, 1>{} {
    }

    /// @brief Constructor initializing the unit with a specific value
    constexpr explicit Hertz(uint32_t v)
        : Unit<uint32_t, 1>{v} {
    }

    /// @brief Copy constructor from const reference
    constexpr Hertz(Hertz const& other)
        : Unit<uint32_t, 1>{other.value()} {
    }

    /// @brief Copy constructor from non-const reference
    constexpr Hertz& operator=(Hertz& other) {
        value_ = other.value();
       return *this;
    }

    /// @brief Copy constructor from const reference
    constexpr Hertz& operator=(Hertz const& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference
    inline Hertz& operator=(Hertz volatile& other) {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from non-const reference to a volatile object
    /// @warning This is an unusual use case and should be used with caution as the object reference is not returned!
    inline void operator=(Hertz& other) volatile {
        value_ = other.value();
    }

    /// @brief Copy constructor from const reference to a volatile object
    inline Hertz volatile& operator=(Hertz const& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Copy constructor from volatile reference to a volatile object
    inline Hertz volatile& operator=(Hertz volatile& other) volatile {
        value_ = other.value();
        return *this;
    }

    /// @brief Addition operator for Hertz
    friend constexpr inline Hertz operator+(Hertz const& lhs, Hertz const& rhs) {
        return Hertz{lhs.value() + rhs.value()};
    }

    /// @brief Subtraction operator for Hertz
    friend constexpr inline Hertz operator-(Hertz const& lhs, Hertz const& rhs) {
        return Hertz{lhs.value() - rhs.value()};
    }

    /// @brief Multiplication operator for Hertz with scalar
    friend constexpr inline Hertz operator*(Hertz const& lhs, uint32_t rhs) {
        return Hertz{lhs.value() * rhs};
    }

    /// @brief Division operator for Hertz with scalar
    friend constexpr inline Hertz operator/(Hertz const& lhs, uint32_t rhs) {
        return Hertz{lhs.value() / rhs};
    }

    /// @brief Multiplication operator for scalar with Hertz
    friend constexpr inline Hertz operator*(uint32_t lhs, Hertz const& rhs) {
        return Hertz{lhs * rhs.value()};
    }

    /// @brief Negation operator for Hertz
    friend constexpr inline Hertz operator-(Hertz const& other) {
        return Hertz{other.value() * static_cast<uint32_t>(-1)};
    }

    /// @brief Equality operator for Hertz
    friend constexpr inline bool operator==(Hertz const& lhs, Hertz const& rhs) {
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

    /// @brief Inequality operator for Hertz
    friend constexpr inline bool operator!=(Hertz const& lhs, Hertz const& rhs) {
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

    /// @brief Less than operator for Hertz
    friend constexpr inline bool operator<(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() < rhs.value();
    }

    /// @brief Less than or equal operator for Hertz
    friend constexpr inline bool operator<=(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() <= rhs.value();
    }

    /// @brief Greater than operator for Hertz
    friend constexpr inline bool operator>(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() > rhs.value();
    }

    /// @brief Greater than or equal operator for Hertz
    friend constexpr inline bool operator>=(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
/// @brief Stream output operator for Hertz
inline std::ostream& operator<<(std::ostream& os, Hertz const& v) {
        os << "Hertz" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
