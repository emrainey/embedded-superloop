#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Watts unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Watts : public Unit<float, 1> {
public:
    using StorageType = float;
    constexpr Watts()
        : Unit<float, 1>{} {
    }
    constexpr explicit Watts(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Watts(Watts& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Watts(Watts const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Watts(Watts volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Watts(Watts const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Watts& operator=(Watts& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Watts& operator=(Watts const& other) {
        value_ = other.value();
        return *this;
    }
    inline Watts& operator=(Watts volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Watts& operator=(Watts const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Watts volatile& operator=(Watts& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Watts volatile& operator=(Watts const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Watts volatile& operator=(Watts volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Watts volatile& operator=(Watts const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Watts operator+(Watts const& lhs, Watts const& rhs) {
        return Watts{lhs.value() + rhs.value()};
    }
    friend constexpr inline Watts operator-(Watts const& lhs, Watts const& rhs) {
        return Watts{lhs.value() - rhs.value()};
    }
    friend constexpr inline Watts operator*(Watts const& lhs, float rhs) {
        return Watts{lhs.value() * rhs};
    }
    friend constexpr inline Watts operator/(Watts const& lhs, float rhs) {
        return Watts{lhs.value() / rhs};
    }
    friend constexpr inline Watts operator*(float lhs, Watts const& rhs) {
        return Watts{lhs * rhs.value()};
    }
    friend constexpr inline Watts operator-(Watts const& other) {
        return Watts{other.value() * static_cast<float>(-1)};
    }
    friend constexpr inline bool operator==(Watts const& lhs, Watts const& rhs) {
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
    friend constexpr inline bool operator!=(Watts const& lhs, Watts const& rhs) {
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
    friend constexpr inline bool operator<(Watts const& lhs, Watts const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Watts const& lhs, Watts const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Watts const& lhs, Watts const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Watts const& lhs, Watts const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Watts const& v) {
        os << "Watts" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
