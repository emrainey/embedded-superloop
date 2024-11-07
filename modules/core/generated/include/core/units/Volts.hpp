#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Volts unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Volts : public Unit<float, 1> {
public:
    using StorageType = float;
    constexpr Volts()
        : Unit<float, 1>{} {
    }
    constexpr explicit Volts(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Volts(Volts& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Volts(Volts const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Volts(Volts volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Volts(Volts const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Volts& operator=(Volts& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Volts& operator=(Volts const& other) {
        value_ = other.value();
        return *this;
    }
    inline Volts& operator=(Volts volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Volts& operator=(Volts const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Volts volatile& operator=(Volts& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Volts volatile& operator=(Volts const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Volts volatile& operator=(Volts volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Volts volatile& operator=(Volts const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Volts operator+(Volts const& lhs, Volts const& rhs) {
        return Volts{lhs.value() + rhs.value()};
    }
    friend constexpr inline Volts operator-(Volts const& lhs, Volts const& rhs) {
        return Volts{lhs.value() - rhs.value()};
    }
    friend constexpr inline Volts operator*(Volts const& lhs, float rhs) {
        return Volts{lhs.value() * rhs};
    }
    friend constexpr inline Volts operator/(Volts const& lhs, float rhs) {
        return Volts{lhs.value() / rhs};
    }
    friend constexpr inline Volts operator*(float lhs, Volts const& rhs) {
        return Volts{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(Volts const& lhs, Volts const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(Volts const& lhs, Volts const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(Volts const& lhs, Volts const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Volts const& lhs, Volts const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Volts const& lhs, Volts const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Volts const& lhs, Volts const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Volts const& v) {
        os << "Volts" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
