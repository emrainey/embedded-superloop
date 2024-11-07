#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Ohms unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Ohms : public Unit<float, 1> {
public:
    using StorageType = float;
    constexpr Ohms()
        : Unit<float, 1>{} {
    }
    constexpr explicit Ohms(float v)
        : Unit<float, 1>{v} {
    }
    // constexpr Ohms(Ohms& other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Ohms(Ohms const& other)
        : Unit<float, 1>{other.value()} {
    }
    // constexpr Ohms(Ohms volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    // constexpr Ohms(Ohms const volatile & other)
    //     : Unit<float, 1>{other.value()} {
    // }
    constexpr Ohms& operator=(Ohms& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Ohms& operator=(Ohms const& other) {
        value_ = other.value();
        return *this;
    }
    inline Ohms& operator=(Ohms volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Ohms& operator=(Ohms const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Ohms volatile& operator=(Ohms& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Ohms volatile& operator=(Ohms const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Ohms volatile& operator=(Ohms volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Ohms volatile& operator=(Ohms const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Ohms operator+(Ohms const& lhs, Ohms const& rhs) {
        return Ohms{lhs.value() + rhs.value()};
    }
    friend constexpr inline Ohms operator-(Ohms const& lhs, Ohms const& rhs) {
        return Ohms{lhs.value() - rhs.value()};
    }
    friend constexpr inline Ohms operator*(Ohms const& lhs, float rhs) {
        return Ohms{lhs.value() * rhs};
    }
    friend constexpr inline Ohms operator/(Ohms const& lhs, float rhs) {
        return Ohms{lhs.value() / rhs};
    }
    friend constexpr inline Ohms operator*(float lhs, Ohms const& rhs) {
        return Ohms{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Ohms const& lhs, Ohms const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Ohms const& v) {
        os << "Ohms" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
