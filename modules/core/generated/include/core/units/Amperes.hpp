#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Amperes unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Amperes : public Unit<float, 1> {
public:
    constexpr Amperes()
        : Unit<float, 1>{} {
    }
    constexpr explicit Amperes(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Amperes(Amperes& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Amperes(Amperes const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Amperes(Amperes volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Amperes(Amperes const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Amperes& operator=(Amperes& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Amperes& operator=(Amperes const& other) {
        value_ = other.value();
        return *this;
    }
    inline Amperes& operator=(Amperes volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Amperes& operator=(Amperes const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Amperes volatile& operator=(Amperes& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Amperes volatile& operator=(Amperes const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Amperes volatile& operator=(Amperes volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Amperes volatile& operator=(Amperes const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Amperes operator+(Amperes const& lhs, Amperes const& rhs) {
        return Amperes{lhs.value() + rhs.value()};
    }
    friend constexpr inline Amperes operator-(Amperes const& lhs, Amperes const& rhs) {
        return Amperes{lhs.value() - rhs.value()};
    }
    friend constexpr inline Amperes operator*(Amperes const& lhs, float rhs) {
        return Amperes{lhs.value() * rhs};
    }
    friend constexpr inline Amperes operator/(Amperes const& lhs, float rhs) {
        return Amperes{lhs.value() / rhs};
    }
    friend constexpr inline Amperes operator*(float lhs, Amperes const& rhs) {
        return Amperes{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(Amperes const& lhs, Amperes const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(Amperes const& lhs, Amperes const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(Amperes const& lhs, Amperes const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Amperes const& lhs, Amperes const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Amperes const& lhs, Amperes const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Amperes const& lhs, Amperes const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Amperes const& v) {
        os << "Amperes" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
