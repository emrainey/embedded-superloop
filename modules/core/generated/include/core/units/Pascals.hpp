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
class Pascals : public Unit<float, 1> {
public:
    using StorageType = float;
    constexpr Pascals()
        : Unit<float, 1>{} {
    }
    constexpr explicit Pascals(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Pascals(Pascals& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Pascals(Pascals const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Pascals(Pascals volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Pascals(Pascals const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Pascals& operator=(Pascals& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Pascals& operator=(Pascals const& other) {
        value_ = other.value();
        return *this;
    }
    inline Pascals& operator=(Pascals volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Pascals& operator=(Pascals const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Pascals volatile& operator=(Pascals& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Pascals volatile& operator=(Pascals const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Pascals volatile& operator=(Pascals volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Pascals volatile& operator=(Pascals const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Pascals operator+(Pascals const& lhs, Pascals const& rhs) {
        return Pascals{lhs.value() + rhs.value()};
    }
    friend constexpr inline Pascals operator-(Pascals const& lhs, Pascals const& rhs) {
        return Pascals{lhs.value() - rhs.value()};
    }
    friend constexpr inline Pascals operator*(Pascals const& lhs, float rhs) {
        return Pascals{lhs.value() * rhs};
    }
    friend constexpr inline Pascals operator/(Pascals const& lhs, float rhs) {
        return Pascals{lhs.value() / rhs};
    }
    friend constexpr inline Pascals operator*(float lhs, Pascals const& rhs) {
        return Pascals{lhs * rhs.value()};
    }
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
    friend constexpr inline bool operator<(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Pascals const& lhs, Pascals const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Pascals const& v) {
        os << "Pascals" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
