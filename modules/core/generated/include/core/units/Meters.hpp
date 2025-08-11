#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Meters unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Meters : public Unit<float, 1> {
public:
    using StorageType = float;
    constexpr Meters()
        : Unit<float, 1>{} {
    }
    constexpr explicit Meters(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Meters(Meters& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Meters(Meters const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Meters(Meters volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Meters(Meters const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Meters& operator=(Meters& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Meters& operator=(Meters const& other) {
        value_ = other.value();
        return *this;
    }
    inline Meters& operator=(Meters volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Meters& operator=(Meters const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Meters volatile& operator=(Meters& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Meters volatile& operator=(Meters const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Meters volatile& operator=(Meters volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Meters volatile& operator=(Meters const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Meters operator+(Meters const& lhs, Meters const& rhs) {
        return Meters{lhs.value() + rhs.value()};
    }
    friend constexpr inline Meters operator-(Meters const& lhs, Meters const& rhs) {
        return Meters{lhs.value() - rhs.value()};
    }
    friend constexpr inline Meters operator*(Meters const& lhs, float rhs) {
        return Meters{lhs.value() * rhs};
    }
    friend constexpr inline Meters operator/(Meters const& lhs, float rhs) {
        return Meters{lhs.value() / rhs};
    }
    friend constexpr inline Meters operator*(float lhs, Meters const& rhs) {
        return Meters{lhs * rhs.value()};
    }
    friend constexpr inline Meters operator-(Meters const& other) {
        return Meters{other.value() * static_cast<float>(-1)};
    }
    friend constexpr inline bool operator==(Meters const& lhs, Meters const& rhs) {
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
    friend constexpr inline bool operator!=(Meters const& lhs, Meters const& rhs) {
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
    friend constexpr inline bool operator<(Meters const& lhs, Meters const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Meters const& lhs, Meters const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Meters const& lhs, Meters const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Meters const& lhs, Meters const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Meters const& v) {
        os << "Meters" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
