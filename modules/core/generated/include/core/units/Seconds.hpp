#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Seconds unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Seconds : public Unit<float, 1> {
public:
    constexpr Seconds()
        : Unit<float, 1>{} {
    }
    constexpr explicit Seconds(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Seconds(Seconds& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Seconds(Seconds const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Seconds(Seconds volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Seconds(Seconds const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Seconds& operator=(Seconds& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Seconds& operator=(Seconds const& other) {
        value_ = other.value();
        return *this;
    }
    inline Seconds& operator=(Seconds volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Seconds& operator=(Seconds const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Seconds volatile& operator=(Seconds& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Seconds volatile& operator=(Seconds const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Seconds volatile& operator=(Seconds volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Seconds volatile& operator=(Seconds const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Seconds operator+(Seconds const& lhs, Seconds const& rhs) {
        return Seconds{lhs.value() + rhs.value()};
    }
    friend constexpr inline Seconds operator-(Seconds const& lhs, Seconds const& rhs) {
        return Seconds{lhs.value() - rhs.value()};
    }
    friend constexpr inline Seconds operator*(Seconds const& lhs, float rhs) {
        return Seconds{lhs.value() * rhs};
    }
    friend constexpr inline Seconds operator/(Seconds const& lhs, float rhs) {
        return Seconds{lhs.value() / rhs};
    }
    friend constexpr inline Seconds operator*(float lhs, Seconds const& rhs) {
        return Seconds{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Seconds const& lhs, Seconds const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Seconds const& v) {
        os << "Seconds" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
