#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Degrees unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Degrees : public Unit<float, 1> {
public:
    using StorageType = float;
    constexpr Degrees()
        : Unit<float, 1>{} {
    }
    constexpr explicit Degrees(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Degrees(Degrees& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Degrees(Degrees const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Degrees(Degrees volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Degrees(Degrees const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Degrees& operator=(Degrees& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Degrees& operator=(Degrees const& other) {
        value_ = other.value();
        return *this;
    }
    inline Degrees& operator=(Degrees volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Degrees& operator=(Degrees const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Degrees volatile& operator=(Degrees& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Degrees volatile& operator=(Degrees const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Degrees volatile& operator=(Degrees volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Degrees volatile& operator=(Degrees const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Degrees operator+(Degrees const& lhs, Degrees const& rhs) {
        return Degrees{lhs.value() + rhs.value()};
    }
    friend constexpr inline Degrees operator-(Degrees const& lhs, Degrees const& rhs) {
        return Degrees{lhs.value() - rhs.value()};
    }
    friend constexpr inline Degrees operator*(Degrees const& lhs, float rhs) {
        return Degrees{lhs.value() * rhs};
    }
    friend constexpr inline Degrees operator/(Degrees const& lhs, float rhs) {
        return Degrees{lhs.value() / rhs};
    }
    friend constexpr inline Degrees operator*(float lhs, Degrees const& rhs) {
        return Degrees{lhs * rhs.value()};
    }
    friend constexpr inline Degrees operator-(Degrees const& other) {
        return Degrees{other.value() * static_cast<float>(-1)};
    }
    friend constexpr inline bool operator==(Degrees const& lhs, Degrees const& rhs) {
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
    friend constexpr inline bool operator!=(Degrees const& lhs, Degrees const& rhs) {
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
    friend constexpr inline bool operator<(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Degrees const& lhs, Degrees const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Degrees const& v) {
        os << "Degrees" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
