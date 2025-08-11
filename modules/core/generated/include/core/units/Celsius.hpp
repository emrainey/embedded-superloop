#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Celsius unit of measurement

#include <type_traits>
#include <cstdint>
#include <cmath>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Celsius : public Unit<float, 1> {
public:
    using StorageType = float;
    constexpr Celsius()
        : Unit<float, 1>{} {
    }
    constexpr explicit Celsius(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Celsius(Celsius& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Celsius(Celsius const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Celsius(Celsius volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Celsius(Celsius const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Celsius& operator=(Celsius& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Celsius& operator=(Celsius const& other) {
        value_ = other.value();
        return *this;
    }
    inline Celsius& operator=(Celsius volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Celsius& operator=(Celsius const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Celsius volatile& operator=(Celsius& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Celsius volatile& operator=(Celsius const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Celsius volatile& operator=(Celsius volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Celsius volatile& operator=(Celsius const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Celsius operator+(Celsius const& lhs, Celsius const& rhs) {
        return Celsius{lhs.value() + rhs.value()};
    }
    friend constexpr inline Celsius operator-(Celsius const& lhs, Celsius const& rhs) {
        return Celsius{lhs.value() - rhs.value()};
    }
    friend constexpr inline Celsius operator*(Celsius const& lhs, float rhs) {
        return Celsius{lhs.value() * rhs};
    }
    friend constexpr inline Celsius operator/(Celsius const& lhs, float rhs) {
        return Celsius{lhs.value() / rhs};
    }
    friend constexpr inline Celsius operator*(float lhs, Celsius const& rhs) {
        return Celsius{lhs * rhs.value()};
    }
    friend constexpr inline Celsius operator-(Celsius const& other) {
        return Celsius{other.value() * static_cast<float>(-1)};
    }
    friend constexpr inline bool operator==(Celsius const& lhs, Celsius const& rhs) {
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
    friend constexpr inline bool operator!=(Celsius const& lhs, Celsius const& rhs) {
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
    friend constexpr inline bool operator<(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Celsius const& lhs, Celsius const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Celsius const& v) {
        os << "Celsius" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
